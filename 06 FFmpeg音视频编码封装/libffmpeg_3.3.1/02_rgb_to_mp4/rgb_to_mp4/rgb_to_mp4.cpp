// FFmpeg是基于C实现的，需要按照C风格的函数进行导入
extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/mathematics.h>
#include <libswscale/swscale.h>
}

#include <iostream>
#define LINE "================================="
using namespace std;

#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avcodec.lib")
#pragma comment(lib,"avutil.lib")
#pragma comment(lib,"swscale.lib")

int main()
{
	char infile[] = "../../rgb_data.npy";
	char outfile[] = "../../rgb.mp4";
	// 注册 muxer, demuxer
	av_register_all();
	avcodec_register_all();

	// 读取rgba数据
	FILE *fp = fopen(infile, "rb");
	if (!fp)
	{
		cerr << "fopen fail." << endl;
		return -1;
	}

	int width = 1280;
	int height = 720;
	int fps = 24;

	// 获取 h264编码器
	AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_H264);
	if (!codec)
	{
		cerr << "avcodec_find_decoder fail." << endl;
		return -1;
	}
	AVCodecContext *pAvCodecCtx = avcodec_alloc_context3(codec); // pAvCodecCtx
	if (!pAvCodecCtx)
	{
		cout << "avcodec_alloc_context3 fail." << endl;
		return -1;
	}
	// 比特率
	pAvCodecCtx->bit_rate = 400000000;
	pAvCodecCtx->width = width;
	pAvCodecCtx->height = height;
	pAvCodecCtx->time_base = { 1,fps };
	pAvCodecCtx->framerate = { fps,1 };
	// 关键帧的画面组(一个i帧+一堆b帧、p帧)
	pAvCodecCtx->gop_size = 50; // 每50帧一个关键帧
	pAvCodecCtx->max_b_frames = 0;
	pAvCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P; // 像素格式
	pAvCodecCtx->codec_id = AV_CODEC_ID_H264;
	pAvCodecCtx->thread_count = 10;
	// 全局的编码信息
	pAvCodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

	int ret = avcodec_open2(pAvCodecCtx, codec, NULL);
	if (ret < 0)
	{
		cout << "avcodec_open2 fail." << endl;
		return -1;
	}
	cout << "avcodec_open2 success!" << endl;

	// (输出的)格式封装上下文
	AVFormatContext *pOavfc = NULL;
	avformat_alloc_output_context2(&pOavfc, 0, 0, outfile);
	// 数据流
	AVStream *pAvs = avformat_new_stream(pOavfc, NULL);
	//pAvs->codec = pAvCodecCtx;
	pAvs->id = 0;
	pAvs->codecpar->codec_tag = 0;
	avcodec_parameters_from_context(pAvs->codecpar, pAvCodecCtx);

	cout << LINE << endl;
	av_dump_format(pOavfc, 0, outfile, 1);
	cout << LINE << endl;

	// rgba -> yuv
	SwsContext *pSwsctx = NULL;
	pSwsctx = sws_getCachedContext(pSwsctx,
		width, height, AV_PIX_FMT_RGBA,	// 输入的像素格式
		width, height, AV_PIX_FMT_YUV420P,// 输出
		SWS_BICUBIC, // 算法
		NULL, NULL, NULL);
	uint8_t *rgba = new unsigned char[width*height * 4]; // 4: b,g,r,a
	AVFrame *yuvFrame = av_frame_alloc();
	yuvFrame->format = AV_PIX_FMT_YUV420P;
	yuvFrame->width = width;
	yuvFrame->height = height;
	// 给yuvFrame缓冲区(yuvFrame->data)设置对齐方式
	ret = av_frame_get_buffer(yuvFrame, 32);
	if (ret < 0)
	{
		cout << "av_frame_get_buffer fail." << endl;
		return -1;
	}

	// 开始写入输出文件 
	ret = avio_open(&pOavfc->pb, outfile, AVIO_FLAG_WRITE);
	if (ret < 0)
	{
		cout << "avio_open fail." << endl;
		return -1;
	}
	ret = avformat_write_header(pOavfc, NULL);
	if (ret < 0)
	{
		cout << "avformat_write_header fail." << endl;
		return -1;
	}

	int64_t timestamp = 0;
	while (1)
	{
		int len = fread(rgba, 1, width*height * 4, fp);
		if (len <= 0) break;

		uint8_t *indata[AV_NUM_DATA_POINTERS] = { 0 };
		indata[0] = rgba;
		int inlinesize[AV_NUM_DATA_POINTERS] = { 0 };
		inlinesize[0] = width * 4;
		// 开始 rgba -> yuv
		ret = sws_scale(pSwsctx, indata, inlinesize, 0, height,
			yuvFrame->data, yuvFrame->linesize); // stride
		if (ret < 0) break;

		// 开始h264编码并写入输出文件
		yuvFrame->pts = timestamp;
		//timestamp += 3600;
		timestamp += pOavfc->streams[0]->time_base.den / fps;

		ret = avcodec_send_frame(pAvCodecCtx, yuvFrame); // 将yuv数据交给编码器进行多线程编码
		if (ret != 0) continue;
		AVPacket pkt;
		av_init_packet(&pkt);
		ret = avcodec_receive_packet(pAvCodecCtx, &pkt); // 接收编码后的packet数据包
		if (ret != 0) continue;

		cout << "<" << pkt.size << ">";

		//av_write_frame(pOavfc, &pkt);
		//av_packet_unref(&pkt);
		av_interleaved_write_frame(pOavfc, &pkt); // 自动释放pkt
	}
	// 写入尾部数据
	av_write_trailer(pOavfc);
	avio_close(pOavfc->pb); // 关闭文件指针
	avformat_free_context(pOavfc); //清理封装输出上下文
	avcodec_close(pAvCodecCtx); //关闭编码器
	avcodec_free_context(&pAvCodecCtx); //清理编码器上下文
	sws_freeContext(pSwsctx); //清理视频重采样上下文
	cout << "\n" << LINE << endl;
	getchar();

	return 0;
}