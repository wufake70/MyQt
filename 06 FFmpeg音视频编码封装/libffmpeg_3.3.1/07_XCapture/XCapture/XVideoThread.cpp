#include "XVideoThread.h"
#include <QScreen>
#include <QDesktopWidget>
#include <QPainter>
#include <QPixelFormat>
#include <QDebug>
#include <QApplication>

QList<QByteArray*> XVideoRecord::rgb_frame_list;

bool XVideoThread::init(quint8 fps, quint16 width, 
				quint16 height, QString output_dir)
{
	this->fps = fps;
	this->width = width;
	this->height = height;
	this->output_dir = output_dir;
	win_id = QApplication::desktop()->winId();

	this->is_init = true;
	this->is_exit = false;
	return true;
}

void XVideoThread::run()
{
	if (!is_init)
	{
		qDebug() << "XVideoThread::run() fail.";
		return;
	}
	connect(this, &XVideoThread::Quited,
		this, &XVideoThread::quit); // quit 只能在当前线程中调用有效
	connect(this, &XVideoThread::Quited,
		this, &XVideoThread::Quit); // quit 只能在当前线程中调用有效

	XVideoRecord record(output_dir, win_id,&is_exit);
	connect(this,SIGNAL(CaptureScreened()),
		&record, SLOT(CaptureScreen()));
	exec();
	is_init = false;
	qDebug() << "v_thread exit.";
}

void XVideoThread::Quit()
{
	is_exit = true;
}

void XVideoRecord::CaptureScreen()
{
	if (*is_exit_ptr) return;
	qDebug() <<"video "<< ++frame_count;

	static QScreen *pScreen = NULL;
	if (!pScreen)
	{
		pScreen = QGuiApplication::primaryScreen();
	}
	// 抓取屏幕
	QPixmap pix = pScreen->grabWindow(win_id);
	QImage::Format fmt = pix.toImage().format();

	qint32 size = pix.toImage().sizeInBytes();

	if (fmt != QImage::Format_RGBA8888)
	{
		pix.toImage().toPixelFormat(QImage::Format_RGBA8888);
		size = pix.toImage().sizeInBytes();
	}
	//file.write(QByteArray((char*)pix.toImage().bits(), size));
	QByteArray *byte_arr_ptr = new QByteArray((char*)pix.toImage().bits(), size);
	XVideoRecord::rgb_frame_list.push_back(byte_arr_ptr);

}

QByteArray* XVideoRecord::GetFrame()
{
	if (XVideoRecord::isEmpty()) return nullptr;
	QByteArray* ret = nullptr;
	ret = XVideoRecord::rgb_frame_list.front();
	XVideoRecord::rgb_frame_list.pop_front();
	return ret;
}