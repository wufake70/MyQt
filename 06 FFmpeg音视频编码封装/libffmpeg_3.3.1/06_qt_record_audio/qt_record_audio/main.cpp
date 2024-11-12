#include <QtCore/QCoreApplication>
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QFile>
#include <QDebug>
#include <iostream>

extern "C" {
#include <libavformat/avformat.h>
#include <libavdevice/avdevice.h>
#include <libavcodec/avcodec.h>
}

#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avdevice.lib")
#pragma comment(lib,"avcodec.lib")

void func1(); // QT实现(仅能录制屏外声音)
void func2(); // FFmpeg实现

//#define NO_FFMPEG

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
#ifdef NO_FFMPEG
	func1();
#else
	func2();
#endif // NO_FFMPEG


}
void func1()
{
	// 麦克风输入设备(仅能录制屏外声音)
	QAudioDeviceInfo inputDevice = QAudioDeviceInfo::defaultInputDevice();
	qDebug() << inputDevice.deviceName();
	QAudioFormat fmt;
	fmt.setSampleRate(44100);
	fmt.setChannelCount(2);
	fmt.setSampleSize(16);
	fmt.setSampleType(QAudioFormat::UnSignedInt);
	fmt.setByteOrder(QAudioFormat::LittleEndian);
	fmt.setCodec("audio/pcm");
	QAudioInput *input = new QAudioInput(inputDevice, fmt);
	QIODevice *pIO = input->start();


	QFile file("../../record.pcm");
	file.open(QIODevice::ReadWrite | QIODevice::Truncate);
	qint8 buffer[1024] = { 0 };
	int size = 0;
	for (;;)
	{
		if (input->bytesReady() < 1024) continue;
		size = pIO->read((char*)buffer, 1024);
		file.write(QByteArray((char*)buffer, size));

		if (file.size() >= 1024 * 1024) break;
		std::cout << size << " ";
	}

	file.close();
	std::cout << "Recording completed and saved to output.pcm" << std::endl;
}

void func2()
{
	avdevice_register_all();

	// 设置输入格式为dshow（DirectShow），用于Windows上的设备
	AVInputFormat* inputFormat = av_find_input_format("dshow");
	if (!inputFormat) {
		std::cerr << "Could not find input format" << std::endl;
		return ;
	}


	// 打开指定音频输入设备，并获取封装上下文
	AVFormatContext* formatContext = nullptr;
	if (avformat_open_input(&formatContext, u8"audio=立体声混音 (Realtek(R) Audio)", inputFormat, nullptr) != 0) {
		std::cerr << "Could not open input" << std::endl;
		return ;
	}

	// 查找流信息
	if (avformat_find_stream_info(formatContext, nullptr) < 0) {
		std::cerr << "Could not find stream info" << std::endl;
		avformat_close_input(&formatContext);
		return ;
	}

	// 查找音频流
	AVStream* audioStream = nullptr;
	for (unsigned i = 0; i < formatContext->nb_streams; ++i) {
		if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
			audioStream = formatContext->streams[i];
			break;
		}
	}
	//audioStream->codecpar->codec_tag = 0;
	
	//audioStream->codecpar->bit_rate = 64 * 1024;
	//audioStream->codecpar->channels = 2;
	//audioStream->codecpar->sample_rate = 44100;
	//audioStream->codecpar->channel_layout = AV_CH_LAYOUT_STEREO;
	
	if (!audioStream) {
		std::cerr << "Could not find audio stream" << std::endl;
		avformat_close_input(&formatContext);
		return ;
	}

	// 打开输出文件
	QFile file("../../record.pcm");
	file.open(QIODevice::Truncate|QIODevice::ReadWrite);

	// 读取帧并写入文件
	AVPacket packet;
	av_init_packet(&packet);

	while (av_read_frame(formatContext, &packet) >= 0) {
		if (packet.stream_index == audioStream->index) {
			file.write(QByteArray((char*)packet.data,packet.size));
			std::cout << packet.size << " ";
		}
		av_packet_unref(&packet);
		if (file.size() >= 1024 * 1024) break;
	}

	// 清理资源
	avformat_close_input(&formatContext);
	file.close();

	std::cout << "Recording completed and saved to output.pcm" << std::endl;
}


