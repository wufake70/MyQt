#pragma once
#include <string>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

struct AVPacket; // 可以不暴露ffmpeg头文件

enum XSAMPLEFMT {
	X_S16 = 1,
	X_FLATP=8
};

// 抽象类接口
class XVideoWriter
{
public:
	// 输入参数
	int inWidth = 1280;
	int inHeight = 720;
	int inPixFmt = 30; // AV_PIX_FMT_BGRA
	// audio
	int inSampleRate = 44100;
	int inChannels = 2;
	XSAMPLEFMT inSampleFmt = X_S16;

	// 输出参数
	int outVBitrate = 4 * 1024 * 1024 * 8/8;
	int outWidth = 1280;
	int outHeight = 720;
	int outFps = 25;
	// audio
	int outABitrate = 64 * 1024;
	int outChannels = 2;
	int outSampleRate = 44100;
	XSAMPLEFMT outSampleType = X_FLATP;
	int outNbSample = 1024; // 一帧音频数据包样本数量

	virtual void Close()=0; // 纯虚函数基类中不实现
	virtual bool Init(const char* path)=0; 
	virtual bool AddVideoStream() = 0;
	virtual bool AddAudioStream() = 0;
	virtual AVPacket *EncodeVideo(uint8 *rgb) = 0;
	virtual AVPacket *EncodeAudio(uint8 *) = 0;
	virtual bool WriteHead() = 0;
	virtual bool WriteFrame(AVPacket*) = 0;
	virtual bool WriteEnd() = 0;
	virtual bool IsHandleVideo() = 0; // 处理音视频同步问题
	static XVideoWriter* Get(uint16 index=0);
	~XVideoWriter();
	std::string filename;

protected:
	XVideoWriter();
};

