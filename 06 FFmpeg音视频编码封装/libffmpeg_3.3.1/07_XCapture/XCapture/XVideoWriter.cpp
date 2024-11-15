#include "XVideoWriter.h"
#include "XAudioThread.h"
#include "XVideoThread.h"
#include <QDebug>
#include <QByteArray>
#include <QProcess>
#include <QDateTime>

extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavutil/opt.h> // 时间戳计算
}

#include <iostream>

#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avcodec.lib")
#pragma comment(lib,"swscale.lib")
#pragma comment(lib,"swresample.lib")
#pragma comment(lib,"libavutil.lib")


/*
工厂模式，对象的创建、销毁全部在cpp文件中实现，
不由调用者管理
*/

// 该类不对外部开放
class CXVideoWriter: public XVideoWriter
{
public:
	// 输出的封装上下文
	AVFormatContext *pOAvfCtx = NULL; // C11后支持在声明中初始化成员变量
	// 音视频编码器上下文
	AVCodecContext *pVCodecCtx = NULL;
	AVCodecContext *pACodecCtx = NULL;
	// 音视频流
	AVStream *pVstream = NULL;
	AVStream *pAstream = NULL;
	// 像素转换上下文、重采样上下文
	SwsContext *pSwsCtx = NULL;
	SwrContext *pSwrCtx = NULL;
	// yuvFrame数据帧
	AVFrame *yuvFrame = NULL;
	AVFrame *pcmFrame = NULL;
	int vPts = 0;
	int aPts = 0;
	void Close()
	{
		if (pOAvfCtx) avformat_free_context(pOAvfCtx); pOAvfCtx = NULL;
		if (pVCodecCtx) {
			avcodec_close(pVCodecCtx);
			avcodec_free_context(&pVCodecCtx);
		}
		if (pACodecCtx) {
			avcodec_close(pACodecCtx);
			avcodec_free_context(&pACodecCtx);
		}
		if (pSwsCtx)
		{
			sws_freeContext(pSwsCtx);
			pSwsCtx = NULL;
		}
		if (pSwrCtx)
		{
			swr_free(&pSwrCtx);
		}
		if (yuvFrame)
		{
			av_frame_free(&yuvFrame);
		}
	}
	bool Init(const char* file_name)
	{
		Close();
		int ret = avformat_alloc_output_context2(&pOAvfCtx,0,0,file_name);
		if (ret < 0)
		{
			std::cout << "Init::avformat_alloc_output_context2 fail." << endl;
			return false;
		}
		filename = file_name;
		return	true;
	}
	bool AddVideoStream()
	{
		if (!pOAvfCtx) return false;
		AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_H264);
		if (!codec)
		{
			std::cerr << "avcodec_find_encoder fail." << endl;
			return false;
		}
		pVCodecCtx = avcodec_alloc_context3(codec);
		if (!pVCodecCtx)
		{
			std::cerr << "avcodec_alloc_context3 fail." << endl;
			return false;
		}
		pVCodecCtx->bit_rate = outVBitrate;
		pVCodecCtx->width = outWidth;
		pVCodecCtx->height = outHeight;
		pVCodecCtx->time_base = { 1,outFps };
		pVCodecCtx->framerate = { outFps,1 };

		pVCodecCtx->gop_size = 50;
		pVCodecCtx->max_b_frames = 0;
		pVCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
		pVCodecCtx->codec_id = AV_CODEC_ID_H264;
		//av_opt_set(pVCodecCtx->priv_data,"preset","superfast",0);// *
		pVCodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

		int ret = avcodec_open2(pVCodecCtx, codec, 0);
		if (ret < 0)
		{
			std::cerr << "avcodec_open2 fail." << endl;
			return false;
		}
		std::cout << "avcodec_open2 success." << endl;

		// 创建流
		pVstream = avformat_new_stream(pOAvfCtx, NULL);
		if (!pVstream) {
			std::cerr << "avformat_new_stream fail." << endl;
			return false;
		}
		// 配置流的参数
		pVstream->codecpar->codec_tag = 0;
		avcodec_parameters_from_context(pVstream->codecpar, pVCodecCtx);

		std::cout << "==================" << endl;
		av_dump_format(pOAvfCtx, 0, filename.c_str(),1);
		std::cout << "==================" << endl;

		pSwsCtx = sws_getCachedContext(pSwsCtx,
			inWidth, inHeight, AV_PIX_FMT_BGRA,
			outWidth, outHeight, AV_PIX_FMT_YUV420P,
			SWS_BICUBIC,0,0,0);
		if (!pSwsCtx)
		{
			std::cerr << "sws_getCachedContext fail." << endl;
			return false;
		}

		if (!yuvFrame)
		{
			yuvFrame = av_frame_alloc();
			yuvFrame->format = AV_PIX_FMT_YUV420P;
			yuvFrame->width = outWidth;
			yuvFrame->height = outHeight;
			yuvFrame->pts = 0;
			ret = av_frame_get_buffer(yuvFrame, 32);
			if (ret < 0)
			{
				std::cerr << "av_frame_get_buffer fail." << endl;
				return false;
			}

			return true;
		}
	}
	bool AddAudioStream()
	{
		if (!pOAvfCtx) return false;
		AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_AAC);
		if (!codec)
		{
			std::cerr << "avcodec_find_encoder fail." << endl;
			return false;
		}
		pACodecCtx = avcodec_alloc_context3(codec);
		if (!pACodecCtx)
		{
			std::cerr << "avcodec_alloc_context3 fail." << endl;
			return false;
		}
		// 配置编码器参数
		pACodecCtx->bit_rate = outABitrate;
		pACodecCtx->sample_rate = outSampleRate;
		pACodecCtx->sample_fmt = (AVSampleFormat)outSampleType;
		pACodecCtx->channels = outChannels;
		pACodecCtx->channel_layout = av_get_default_channel_layout(outChannels);
		pACodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

		int ret = avcodec_open2(pACodecCtx, codec, 0);
		if (ret < 0)
		{
			std::cerr << "audio avcodec_open2 fail." << endl;
			return false;
		}

		// 新增音频流
		pAstream = avformat_new_stream(pOAvfCtx, codec);
		if (!pAstream)
		{
			std::cerr << "audio avformat_new_stream fail." << endl;
			return false;
		}
		pAstream->codecpar->codec_tag = 0;
		avcodec_parameters_from_context(pAstream->codecpar,pACodecCtx);

		std::cout << "==================" << endl;
		av_dump_format(pOAvfCtx, 0, filename.c_str(), 1);
		std::cout << "==================" << endl;

		// 重采样上下文
		pSwrCtx = swr_alloc_set_opts(pSwrCtx,
			pACodecCtx->channel_layout,pACodecCtx->sample_fmt,pACodecCtx->sample_rate,
			av_get_default_channel_layout(inChannels),(AVSampleFormat)inSampleFmt,inSampleRate,
			0, 0);
		ret = swr_init(pSwrCtx);
		if (ret < 0)
		{
			std::cerr << "audio swr_init fail." << endl;
			return false;
		}
		if (!pcmFrame)
		{
			pcmFrame = av_frame_alloc();
			pcmFrame->format = pACodecCtx->sample_fmt;
			pcmFrame->channels = pACodecCtx->channels;
			pcmFrame->channel_layout = pACodecCtx->channel_layout;
			pcmFrame->nb_samples = outNbSample; // 一帧音频数据包样本数量
			ret = av_frame_get_buffer(pcmFrame, 0);
			if (ret < 0)
			{
				std::cerr << "av_frame_get_buffer fail." << endl;
				return false;
			}
		}
		return true;
	}
	AVPacket *EncodeVideo(uint8 *rgb)
	{
		AVPacket *pPkt = NULL;
		uint8 *indata[AV_NUM_DATA_POINTERS] = { 0 };
		indata[0] = rgb;
		int indataSize[AV_NUM_DATA_POINTERS] = { 0 };
		indataSize[0] = inWidth * 4;

		// rgb -> yuvFrame
		int ret = sws_scale(pSwsCtx, indata, indataSize,
			0, inHeight,
			yuvFrame->data,yuvFrame->linesize);
		if (ret < 0) return NULL;

		yuvFrame->pts = vPts;
		// 设置yuvFrame数据帧pts
		vPts++;
		//vPts += pOAvfCtx->streams[0]->time_base.den / outFps;

		// 开始编码
		ret = avcodec_send_frame(pVCodecCtx, yuvFrame);
		if (ret != 0)
		{
			return NULL;
		}
		pPkt = av_packet_alloc();
		av_init_packet(pPkt);
		ret = avcodec_receive_packet(pVCodecCtx, pPkt);
		if (ret != 0 || pPkt->size<=0)
		{
			av_packet_free(&pPkt);
			return NULL;
		}
		// **设置packet数据包时间戳**
		av_packet_rescale_ts(pPkt, pVCodecCtx->time_base, pVstream->time_base);
		// **设置流的索引**
		pPkt->stream_index = pVstream->index;
		return pPkt;
	}
	AVPacket *EncodeVideo()
	{
		int ret = avcodec_send_frame(pVCodecCtx, NULL);


		return NULL;
	}
	AVPacket *EncodeAudio(uint8 *pcm)
	{
		// 音频重采样
		uint8_t *indata[AV_NUM_DATA_POINTERS] = { 0 };
		indata[0] = pcm;
		int ret = swr_convert(pSwrCtx, pcmFrame->data, pcmFrame->nb_samples,
			(const uint8_t **)indata, pcmFrame->nb_samples);
		//std::cout << "<" << ret << ">";

		// 开始编码
		ret = avcodec_send_frame(pACodecCtx, pcmFrame);
		if (ret != 0) return NULL;
		AVPacket *pPkt = av_packet_alloc();
		av_init_packet(pPkt);
		ret = avcodec_receive_packet(pACodecCtx, pPkt);
		if (ret != 0 || pPkt->size <= 0)
		{
			av_packet_free(&pPkt);
			return NULL;
		}
		// 设置流的索引
		pPkt->stream_index = pAstream->index;
		// **设置packet数据包时间戳**
		pPkt->pts = aPts;
		pPkt->dts = pPkt->pts;
		aPts += av_rescale_q(pcmFrame->nb_samples, 
			{ 1,pACodecCtx->sample_rate }, 
			pACodecCtx->time_base); // 每一帧数据所增加的时间单位
		return pPkt;
	}

	bool WriteHead()
	{
		if (!pOAvfCtx) return false;
		int ret = avio_open(&pOAvfCtx->pb, filename.c_str(), AVIO_FLAG_WRITE);
		if (ret < 0)
		{
			std::cerr << "avio_open fail." << endl;
			return false;
		}
		ret = avformat_write_header(pOAvfCtx, NULL);
		if (ret < 0)
		{
			std::cerr << "avformat_write_header fail." << endl;
			return false;
		}

		return true;
	}
	bool WriteFrame(AVPacket* pPkt)
	{
		if (!pOAvfCtx || !pPkt || pPkt->size == 0) return false;
		// packet 写入并自动释放
		if(av_interleaved_write_frame(pOAvfCtx,pPkt)!=0) return false;
		return true;
	}
	bool WriteEnd()
	{
		if (!pOAvfCtx || !pOAvfCtx->pb) return false;
		if (av_write_trailer(pOAvfCtx) != 0)
		{
			std::cerr << "av_write_trailer fail." << endl;
			return false;
		}
		if (avio_close(pOAvfCtx->pb) != 0)
		{
			std::cerr << "avio_close fail." << endl;
			return false;
		}
		Close();
		return true;
	}
	bool IsHandleVideo()
	{
		if (!pOAvfCtx || !pVstream || !pAstream) return false;
		int ret = av_compare_ts(vPts, pVCodecCtx->time_base, 
			aPts, pACodecCtx->time_base);
		if (ret <= 0) return true;
		return false;
	}
};

XVideoWriter *XVideoWriter::Get(uint16 index)
{
	static bool isfirst = true;
	if (isfirst)
	{
		av_register_all(); // 注册封装器
		avcodec_register_all(); // 注册编解码器
		isfirst = false;
	}

	static CXVideoWriter wrs[255 * 255];
	return &wrs[index];
}

XVideoWriter::XVideoWriter()
{

}

XVideoWriter::~XVideoWriter() {

}
void XWriteThread::run()
{
	if (!is_init) return;

	connect(this, SIGNAL(Quited()),
		this, SLOT(quit()));
	connect(this, SIGNAL(Quited()),
		this, SLOT(Quit()));

	write_thread_ptr = thread();
	XVideoWriter *xvw = XVideoWriter::Get();
	xvw->Init(file_name.toStdString().c_str());
	// video
	xvw->outFps = this->fps;
	xvw->outWidth = this->width;
	xvw->outHeight = this->height;
	xvw->inWidth = this->width;
	xvw->inHeight = this->height;

	xvw->AddVideoStream();
	//xvw->AddAudioStream();

	quint8 *rgb = nullptr;
	quint8 *pcm = nullptr;

	qDebug() << (xvw->WriteHead() ? u8"WriteHead() success." : u8"WriteHead() fail.") ;
	int lossVFrame = 1; // 统计视频后面的数据帧
	while (!is_exit)
	{
		AVPacket *pPkt = NULL;
		// video
		if (!XVideoRecord::isEmpty())
		{
			QByteArray *byte_arr_ptr = XVideoRecord::GetFrame();
			if (!byte_arr_ptr) continue;
			rgb = (quint8*)byte_arr_ptr->data();
			if (!rgb)
			{
				delete byte_arr_ptr;
				byte_arr_ptr = nullptr;
				rgb = nullptr;
				if (!--lossVFrame) break;
			}
			pPkt = xvw->EncodeVideo(rgb);
			if (pPkt)
			{
				std::cout << ".";
				xvw->WriteFrame(pPkt);
			}
			else {
				std::cout << "-";
				lossVFrame++;
			}
			delete byte_arr_ptr;
			byte_arr_ptr = nullptr;
			rgb = nullptr;
		}


	}
	exec();
	rgb = new quint8[width*height * 4];
	memset(rgb, 0, width*height * 4);
	while(--lossVFrame)
	{

		AVPacket *pPkt = NULL;
		pPkt = xvw->EncodeVideo(rgb);
		if (pPkt)
		{
			std::cout << ".";
			xvw->WriteFrame(pPkt);
		}
		else {
			std::cout << "-";
			//lossVFrame++;
		}
	}
	delete rgb;

	std::cout << endl;
	std::cout << (xvw->WriteEnd() ? "WriteEnd() success." : "WriteEnd fail.") << endl;

	// 音视频合并
	std::cout << "\n\nvideo+audio ." << endl;
	QString ffmpeg_cmd = tr("./ffmpeg -i %1/test.mp4 "
							"-f s16le -ar 44100 -ac 2 "
							"-i %2/test.pcm -c:v copy "
							"-c:a aac -strict experimental "
							"-y %3.mp4").
		arg(output_dir).
		arg(output_dir).
		arg(output_dir+"/"+QDateTime::currentDateTime().toString("yyyy_MM_dd_hh-mm"));

	QProcess process;
	process.start(ffmpeg_cmd);
	process.waitForFinished();
	// 读取命令输出
	QByteArray output = process.readAllStandardOutput();

	// 将输出转换为字符串并打印
	QString outputStr = QString::fromLocal8Bit(output);
	qDebug() << "Command output:" << outputStr;
}

bool XWriteThread::init(quint8 fps, quint16 width, quint16 height, QString output_dir)
{
	this->fps = fps;
	this->width = width;
	this->height = height;
	this->output_dir = output_dir;
	this->file_name = output_dir + "/test.mp4";

	is_init = true;
	is_exit = false;
	return true;
}
void XWriteThread::Quit()
{
	while (!XVideoRecord::isEmpty());
	//while (!XAudioRecord::isEmpty());
	is_exit = true;
	is_init = false;
}