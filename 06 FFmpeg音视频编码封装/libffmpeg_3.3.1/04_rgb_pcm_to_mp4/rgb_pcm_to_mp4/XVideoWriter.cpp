#include "XVideoWriter.h"

extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavutil/opt.h> // 时间戳计算
}

#include <iostream>
using namespace std;

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
		//if (pOAvfCtx) avformat_free_context(pOAvfCtx); pOAvfCtx = NULL;
		if (pOAvfCtx) avformat_close_input(&pOAvfCtx); // 同上
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
	bool Init(const char* path)
	{
		Close();
		int ret = avformat_alloc_output_context2(&pOAvfCtx,0,0,path);
		if (ret < 0)
		{
			cout << "Init::avformat_alloc_output_context2 fail." << endl;
			return false;
		}
		filename = path;
		return	true;
	}
	bool AddVideoStream()
	{
		if (!pOAvfCtx) return false;
		AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_H264);
		if (!codec)
		{
			cerr << "avcodec_find_encoder fail." << endl;
			return false;
		}
		pVCodecCtx = avcodec_alloc_context3(codec);
		if (!pVCodecCtx)
		{
			cerr << "avcodec_alloc_context3 fail." << endl;
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
			cerr << "avcodec_open2 fail." << endl;
			return false;
		}
		cout << "avcodec_open2 success." << endl;

		// 创建流
		pVstream = avformat_new_stream(pOAvfCtx, NULL);
		if (!pVstream) {
			cerr << "avformat_new_stream fail." << endl;
			return false;
		}
		// 配置流的参数
		pVstream->codecpar->codec_tag = 0;
		avcodec_parameters_from_context(pVstream->codecpar, pVCodecCtx);

		cout << "==================" << endl;
		av_dump_format(pOAvfCtx, 0, filename.c_str(),1);
		cout << "==================" << endl;

		pSwsCtx = sws_getCachedContext(pSwsCtx,
			inWidth, inHeight, AV_PIX_FMT_BGRA,
			outWidth, outHeight, AV_PIX_FMT_YUV420P,
			SWS_BICUBIC,0,0,0);
		if (!pSwsCtx)
		{
			cerr << "sws_getCachedContext fail." << endl;
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
				cerr << "av_frame_get_buffer fail." << endl;
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
			cerr << "avcodec_find_encoder fail." << endl;
			return false;
		}
		pACodecCtx = avcodec_alloc_context3(codec);
		if (!pACodecCtx)
		{
			cerr << "avcodec_alloc_context3 fail." << endl;
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
			cerr << "audio avcodec_open2 fail." << endl;
			return false;
		}

		// 新增音频流
		pAstream = avformat_new_stream(pOAvfCtx, codec);
		if (!pAstream)
		{
			cerr << "audio avformat_new_stream fail." << endl;
			return false;
		}
		pAstream->codecpar->codec_tag = 0;
		avcodec_parameters_from_context(pAstream->codecpar,pACodecCtx);

		cout << "==================" << endl;
		av_dump_format(pOAvfCtx, 0, filename.c_str(), 1);
		cout << "==================" << endl;

		// 重采样上下文
		pSwrCtx = swr_alloc_set_opts(pSwrCtx,
			pACodecCtx->channel_layout,pACodecCtx->sample_fmt,pACodecCtx->sample_rate,
			av_get_default_channel_layout(inChannels),(AVSampleFormat)inSampleFmt,inSampleRate,
			0, 0);
		ret = swr_init(pSwrCtx);
		if (ret < 0)
		{
			cerr << "audio swr_init fail." << endl;
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
				cerr << "av_frame_get_buffer fail." << endl;
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
		if (ret != 0) return NULL;
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
	AVPacket *EncodeAudio(uint8 *pcm)
	{
		// 音频重采样
		uint8_t *indata[AV_NUM_DATA_POINTERS] = { 0 };
		indata[0] = pcm;
		int ret = swr_convert(pSwrCtx, pcmFrame->data, pcmFrame->nb_samples,
			(const uint8_t **)indata, pcmFrame->nb_samples);
		//cout << "<" << ret << ">";

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
			cerr << "avio_open fail." << endl;
			return false;
		}
		ret = avformat_write_header(pOAvfCtx, NULL);
		if (ret < 0)
		{
			cerr << "avformat_write_header fail." << endl;
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
			cerr << "av_write_trailer fail." << endl;
			return false;
		}
		if (avio_close(pOAvfCtx->pb) != 0)
		{
			cerr << "avio_close fail." << endl;
			return false;
		}
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