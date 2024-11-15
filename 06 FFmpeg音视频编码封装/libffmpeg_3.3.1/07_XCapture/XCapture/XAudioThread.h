#pragma once
#include <QThread>
#include <QMutex>
#include <QList>
#include <QByteArray>
#include <QFile>



class XAudioRecord : public QObject
{
	Q_OBJECT

	QFile file;
	const bool *is_exit_ptr=nullptr;

public slots:
	void CaptureAudio();
private:
	static QList<QByteArray*> pcm_frame_list;
public:
	static QByteArray* GetFrame();
	inline static bool isEmpty() {
		return XAudioRecord::pcm_frame_list.size() == 0 ? true : false;
	};

	int frame_count = 0;
	XAudioRecord(QString output_dir, const bool *is_exit_ptr) {
		this->frame_count = 0;
		this->is_exit_ptr = is_exit_ptr;
		this->file.setFileName(output_dir + "/" + "test.pcm");
		this->file.open(QIODevice::Truncate | QIODevice::ReadWrite);
	}

	~XAudioRecord() {
		file.close();
	}

};


class XAudioThread:public QThread
{
	Q_OBJECT
signals:
	void CaptureAudioed();
	void Quited();
public slots:
	void Quit();
public:
	QString output_dir;
	
	bool is_init = false;
	bool is_exit = false;
	bool init(QString output_dir);
	static XAudioThread *Get()
	{
		static XAudioThread thread;
		return &thread;
	}
	void run() override;

protected:
	XAudioThread()
	{

	}
	~XAudioThread()
	{

	}
};

