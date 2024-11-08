// FFmpeg是基于C实现的，需要按照C风格的函数进行导入
extern "C"
{
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <libavutil/mathematics.h>
	#include <libswscale/swscale.h>
	#include  <libswresample/swresample.h>
}

#include <iostream>
#define START cout << "===============START==================" << endl
#define SEPARATOR cout << "================SEPARATOR=================" << endl
#define END cout << "===============END==================" << endl
using namespace std;

#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avcodec.lib")
#pragma comment(lib,"avutil.lib")
#pragma comment(lib,"swscale.lib")
#pragma comment(lib,"swresample.lib")

int main()
{
	START;
	char infile[] = "../../16.wav";
	char outfile[] = "../../acc.mp4";
	// 注册 muxer, demuxer
	av_register_all();
	avcodec_register_all();

	AVCodec *pAccCodec = avcodec_find_encoder(AV_CODEC_ID_AAC);
	if (!pAccCodec)
	{
		cerr << "avcodec_find_encoder fail." << endl;
		return -1;
	}
	AVCodecContext *pAvCodecCtx = avcodec_alloc_context3(pAccCodec);
	if (!pAvCodecCtx)
	{
		cerr << "avcodec_alloc_context3 fail." << endl;
		return -1;
	}
	// 配置上下文参数
	pAvCodecCtx->bit_rate = 64 * 1024; // 码率
	pAvCodecCtx->sample_rate = 44100; // 采样率
	pAvCodecCtx->sample_fmt = AV_SAMPLE_FMT_FLTP; // 采样格式
	pAvCodecCtx->channel_layout = AV_CH_LAYOUT_STEREO; // 立体声
	pAvCodecCtx->channels = 2; // 双声道
	pAvCodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
	int ret = avcodec_open2(pAvCodecCtx,pAccCodec, NULL);
	if (ret < 0)
	{
		cerr << "avcodec_open2 fail." << endl;
		return -1;
	}
	cout << "avcodec_open2 success." << endl;
	// 创建输出封装的上下文
	AVFormatContext *pOavfCtx = NULL;
	avformat_alloc_output_context2(&pOavfCtx,NULL,NULL,outfile);
	if (!pOavfCtx)
	{
		cout << "avformat_alloc_output_context2 fail." << endl;
		return -1;
	}
	AVStream *pAvs = avformat_new_stream(pOavfCtx,NULL);
	pAvs->codecpar->codec_tag = 0;
	avcodec_parameters_from_context(pAvs->codecpar,pAvCodecCtx);
	SEPARATOR;
	av_dump_format(pOavfCtx, 0, outfile, 1);
	SEPARATOR;

	// 打开文件
	ret = avio_open(&pOavfCtx->pb,outfile,AVIO_FLAG_WRITE);
	if (ret < 0)
	{
		cout << "avio_open fail." << endl;
		return -1;
	}
	// 写入头部信息
	ret = avformat_write_header(pOavfCtx, NULL);
	if (ret < 0)
	{
		cerr << "avformat_write_header fail." << endl;
		return -1;
	}

	// 音频重采样上下文
	SwrContext *pSwrCtx=NULL;
	pSwrCtx = swr_alloc_set_opts(pSwrCtx,
		// 输出格式
		pAvCodecCtx->channel_layout,
		pAvCodecCtx->sample_fmt,
		pAvCodecCtx->sample_rate,
		// 输入格式
		AV_CH_LAYOUT_STEREO,
		AV_SAMPLE_FMT_S16, 44100,
		0, 0);
	if (!pSwrCtx)
	{
		cerr << "swr_alloc_set_opts fail." << endl;
		return -1;
	}
	ret = swr_init(pSwrCtx);
	if (ret < 0)
	{
		cerr << "swr_init fail." << endl;
		return -1;
	}

	// 数据帧
	AVFrame *pAvframe = av_frame_alloc();
	pAvframe->format = AV_SAMPLE_FMT_FLTP;
	pAvframe->channels = 2;
	pAvframe->channel_layout = AV_CH_LAYOUT_STEREO;
	pAvframe->nb_samples = 1024; // 一帧存放的数据样本
	ret = av_frame_get_buffer(pAvframe, 0);
	if (ret < 0)
	{
		cerr << "av_frame_get_buffer fail." << endl;
		return -1;
	}

	int readsize = pAvframe->nb_samples * 2 * 2; // 样本数*单位大小*通道数
	uint8_t *pcm = new uint8_t[readsize];
	FILE *fp = fopen(infile, "rb");
	while (1)
	{
		int len = fread(pcm, 1, readsize, fp);
		if (len <= 0) break;
		// 开始重采样
		ret = swr_convert(pSwrCtx, pAvframe->data, pAvframe->nb_samples,
			(const uint8_t **)&pcm, pAvframe->nb_samples);
		if (ret <= 0) break;
		cout << "<" << len << ">";

		// 开始编码
		ret = avcodec_send_frame(pAvCodecCtx, pAvframe);
		if (ret != 0) continue;
		AVPacket pkt;
		av_init_packet(&pkt);
		ret = avcodec_receive_packet(pAvCodecCtx, &pkt);
		if (ret != 0) continue;
		av_interleaved_write_frame(pOavfCtx, &pkt);
	}

	ret = av_write_trailer(pOavfCtx);
	if (ret < 0)
	{
		cerr << "av_write_trailer fail." << endl;
		return -1;
	}
	avio_close(pOavfCtx->pb);
	av_frame_free(&pAvframe);
	avformat_free_context(pOavfCtx);
	avcodec_free_context(&pAvCodecCtx);

	getchar();

	return 0;
}