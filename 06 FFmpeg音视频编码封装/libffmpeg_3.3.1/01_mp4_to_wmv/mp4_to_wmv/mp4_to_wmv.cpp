
// FFmpeg是基于C实现的，需要按照C风格的函数进行导入
extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/mathematics.h>
}
#include <iostream>
#define LINE "========================="
using namespace std;

#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avcodec.lib")
#pragma comment(lib,"avutil.lib")

int main()
{
	char infile[] = "../../test.mp4";
	char outfile[] = "../../test.mov";
	// 注册 muxer, demuxer
	av_register_all();

	// 音视频格式容器
	AVFormatContext *pIc = NULL;
	avformat_open_input(&pIc,infile,0,0);
	if (!pIc)
	{ 
		cerr << "avformat_open_input fail." << endl;
		return -1;
	}
	AVFormatContext *pOc = NULL;
	avformat_alloc_output_context2(&pOc,0,0,outfile);
	if (!pOc)
	{
		cerr << "avformat_alloc_output_context2 fail." << endl;
		return -1;
	}

	// 创建流
	AVStream *pVideoStream = avformat_new_stream(pOc, NULL);
	AVStream *pAudioStream = avformat_new_stream(pOc, NULL);
	// 编码器参数复制,pIc->streams是个数组
	avcodec_parameters_copy(pVideoStream->codecpar, pIc->streams[0]->codecpar);
	avcodec_parameters_copy(pAudioStream->codecpar, pIc->streams[1]->codecpar);
	pVideoStream->codecpar->codec_tag = 0;
	pAudioStream->codecpar->codec_tag = 0;
	// 查看输入输出流信息
	av_dump_format(pIc, 0, infile, 0);
	cout << LINE << LINE << endl;
	av_dump_format(pOc, 0, outfile, 1);

	// 文件打开
	int ret = avio_open(&pOc->pb, outfile, AVIO_FLAG_WRITE);
	if (ret<0)
	{
		cerr << "avio_open fail." << endl;
		return -1;
	}
	// 头部信息
	ret = avformat_write_header(pOc, NULL);
	if (ret < 0)
	{
		cerr << "avformat_write_header fail." << endl;
		return -1;
	}
	AVPacket pkt;
	// 逐帧写入
	while (1)
	{
		ret = av_read_frame(pIc, &pkt);
		if (ret < 0) break;
		// 计算pts(画面帧要显示的时间戳)
		pkt.pts = av_rescale_q_rnd(pkt.pts,
			pIc->streams[pkt.stream_index]->time_base,
			pOc->streams[pkt.stream_index]->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		// 计算dts(画面帧要解码时的时间戳)
		pkt.dts = av_rescale_q_rnd(pkt.dts,
			pIc->streams[pkt.stream_index]->time_base,
			pOc->streams[pkt.stream_index]->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		pkt.pos = -1; 
		pkt.duration = av_rescale_q_rnd(pkt.duration,
			pIc->streams[pkt.stream_index]->time_base,
			pOc->streams[pkt.stream_index]->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));

		av_write_frame(pOc, &pkt);
		av_packet_unref(&pkt);
	}
	// 写入尾部信息
	av_write_trailer(pOc);

	// 关闭文件
	avio_close(pOc->pb);
	cout << "mp4 to wmv is OK." << endl;
	getchar();

	return 0;
}