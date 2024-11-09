#include "XVideoWriter.h"
#include <iostream>

using namespace std;

void main()
{
	char *infile1 = (char*)"../../test.rgb";
	char *infile2 = (char*)"../../test.pcm";
	char *outfile = (char*)"../../04_out.mp4";
	XVideoWriter *xw = XVideoWriter::Get();
	cout << (xw->Init(outfile) ? "Init() success." : "Init() fail.") << endl;;
	xw->AddVideoStream();
	xw->AddAudioStream();

	FILE *fp = fopen(infile1, "rb");
	FILE *fp2 = fopen(infile2, "rb");
	if (!fp || !fp2)
	{
		cerr << "fopen fail." << endl;
		return;
	}
	int vFrameSize = xw->inWidth*xw->inHeight * 4;
	uint8 *rgb = new uint8[vFrameSize];
	int aFrameSize = xw->outNbSample*xw->outChannels * 2;
	uint8 *pcm = new uint8[aFrameSize];

	cout << (xw->WriteHead() ? "WriteHead() success." : "WriteHead() fail.") << endl;
	int lossVFrame = 1; // 统计视频后面的数据帧
	int lossAFrame = 1; 
	while (1)
	{
		int len = 0;
		AVPacket *pPkt = NULL;
		if (xw->IsHandleVideo())
		{
			len = fread(rgb, 1, vFrameSize, fp);
			if (len <= 0)
			{
				if(!--lossVFrame) break;
			}
			pPkt= xw->EncodeVideo(rgb);
			if (pPkt)
			{
				cout << ".";
				xw->WriteFrame(pPkt);
			}
			else {
				cout << "-";
				lossVFrame++;
			}
		}
		else// audio
		{
			len = fread(pcm, 1, aFrameSize, fp2);
			if (len <= 0)
			{
				if(!--lossAFrame)	break;
			}
			pPkt = xw->EncodeAudio(pcm);
			if (pPkt)
			{
				cout << ".";
				xw->WriteFrame(pPkt);
			}
			else
			{
				cout << "-";
				lossAFrame++;
			}
		}
	}
	// 处理流媒体后面的数据帧
	while (1)
	{
		int len = 0;
		AVPacket *pPkt = NULL;
		if (lossVFrame)
		{
			len = fread(rgb, 1, vFrameSize, fp);
			if (len <= 0)
			{
				if (!--lossVFrame) break;
			}
			pPkt = xw->EncodeVideo(rgb);
			if (pPkt)
			{
				cout << ".";
				xw->WriteFrame(pPkt);
			}
			else {
				cout << "-";
				lossVFrame++;
			}
		}
		else// audio
		{
			len = fread(pcm, 1, aFrameSize, fp2);
			if (len <= 0)
			{
				if (!--lossAFrame)	break;
			}
			pPkt = xw->EncodeAudio(pcm);
			if (pPkt)
			{
				cout << ".";
				xw->WriteFrame(pPkt);
			}
			else
			{
				cout << "-";
				lossAFrame++;
			}
		}
	}
	cout << endl;
	cout << (xw->WriteEnd() ? "WriteEnd() success." : "WriteEnd fail.") << endl;
	fclose(fp);
	fclose(fp2);
	delete rgb;
	delete pcm;
	rgb = NULL;
	pcm = NULL;
	getchar();
	
}
