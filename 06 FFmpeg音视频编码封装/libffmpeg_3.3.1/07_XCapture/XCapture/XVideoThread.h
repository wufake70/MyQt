#pragma once
#include <QThread>
#include <QMutex>
#include <QList>
#include <QByteArray>
#include <QFile>
#include <QGuiApplication>

class XVideoRecord : public QObject
{
	Q_OBJECT

		WId win_id;
		QFile file;
		const bool *is_exit_ptr;
public slots:
	void CaptureScreen();

private:
	static QList<QByteArray*> rgb_frame_list;
public:
	static QByteArray* GetFrame();
	inline static bool isEmpty() {
		return XVideoRecord::rgb_frame_list.size()==0?true:false;
	};

	int frame_count = 0;
	XVideoRecord(QString output_dir, WId win_id,const bool *is_exit_ptr) {
		this->frame_count = 0;
		this->is_exit_ptr = is_exit_ptr;
		this->win_id = win_id;
		//this->file.setFileName(output_dir + "/" + "test.rgb");
		//this->file.open(QIODevice::Truncate | QIODevice::ReadWrite);
	}

	~XVideoRecord() {
		//file.close();
	}

};

class XVideoThread: public QThread
{
	Q_OBJECT
signals:
	void CaptureScreened();
	void Quited();

public slots:
	void Quit();

public:
	quint8 fps;
	quint16 width;
	quint16 height;
	QString output_dir;
	WId win_id;
	
	bool is_init = false;
	bool is_exit = false;
	bool init(quint8 fps,quint16 width,quint16 height,QString output_dir);
	static XVideoThread *Get()
	{
		static XVideoThread thread;
		return &thread;
	}
	void run() override;

protected:
	XVideoThread()
	{

	}
	~XVideoThread()
	{

	}
};

