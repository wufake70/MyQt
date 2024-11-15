#include "XAudioThread.h"

#include <QScreen>
#include <QDesktopWidget>
#include <QPainter>
#include <QPixelFormat>
#include <QDebug>
#include <QGuiApplication>
#include <QApplication>

extern "C" {
#include <libavformat/avformat.h>
#include <libavdevice/avdevice.h>
#include <libavcodec/avcodec.h>
}

#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avdevice.lib")
#pragma comment(lib,"avcodec.lib")


QList<QByteArray*> XAudioRecord::pcm_frame_list;

bool XAudioThread::init(QString output_dir)
{

	this->output_dir = output_dir;

	this->is_exit = false;
	this->is_init = true;
	return true;
}

void XAudioThread::run()
{
	if (!is_init)
	{
		qDebug() << "XAudioThread::run() fail.";
		return;
	}
	connect(this, &XAudioThread::Quited,
		this, &XAudioThread::Quit); // quit 只能在当前线程中调用有效
	connect(this, &XAudioThread::Quited,
		this, &XAudioThread::quit); // quit 只能在当前线程中调用有效
	XAudioRecord record(output_dir,&is_exit);

	connect(this, SIGNAL(CaptureAudioed()),
		&record, SLOT(CaptureAudio()));
	exec();
	is_init = false;
	qDebug() << "a_thread exit.";
}

void XAudioThread::Quit()
{
	is_exit = true;
}

void XAudioRecord::CaptureAudio()
{

	avdevice_register_all();

	// 设置输入格式为dshow（DirectShow），用于Windows上的设备
	AVInputFormat* inputFormat = av_find_input_format("dshow");
	if (!inputFormat) {
		qDebug() << "Could not find input format" ;
		return;
	}


	// 打开指定音频输入设备，并获取封装上下文
	AVFormatContext* formatContext = nullptr;
	if (avformat_open_input(&formatContext, u8"audio=立体声混音 (Realtek(R) Audio)", inputFormat, nullptr) != 0) {
		qDebug() << "Could not open input" ;
		return;
	}

	// 查找流信息
	if (avformat_find_stream_info(formatContext, nullptr) < 0) {
		qDebug() << "Could not find stream info" ;
		avformat_close_input(&formatContext);
		return;
	}

	// 查找音频流
	AVStream* audioStream = nullptr;
	for (unsigned i = 0; i < formatContext->nb_streams; ++i) {
		if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
			audioStream = formatContext->streams[i];
			break;
		}
	}
	audioStream->codecpar->codec_tag = 0;

	audioStream->codecpar->bit_rate = 64 * 1024;
	audioStream->codecpar->channels = 2;
	audioStream->codecpar->sample_rate = 44100;
	audioStream->codecpar->channel_layout = AV_CH_LAYOUT_STEREO;

	if (!audioStream) {
		qDebug() << "Could not find audio stream" ;
		avformat_close_input(&formatContext);
		return;
	}

	// 读取帧并写入文件
	AVPacket packet;
	av_init_packet(&packet);
	while (1) {
		av_read_frame(formatContext, &packet);
		if (packet.stream_index == audioStream->index) 
		{
			qDebug() << "audio " << ++frame_count;
			file.write(QByteArray((char*)packet.data, packet.size));
			//QByteArray * byte_arr_ptr = new QByteArray((char*)packet.data, packet.size);
			//XAudioRecord::pcm_frame_list.push_back(byte_arr_ptr);

		}
		av_packet_unref(&packet);
		if(*is_exit_ptr) break;
	}

	// 清理资源
	avformat_close_input(&formatContext);

}

QByteArray* XAudioRecord::GetFrame()
{
	if (XAudioRecord::isEmpty()) return nullptr;
	QByteArray* ret = nullptr;
	ret = XAudioRecord::pcm_frame_list.front();
	XAudioRecord::pcm_frame_list.pop_front();
	return ret;
}