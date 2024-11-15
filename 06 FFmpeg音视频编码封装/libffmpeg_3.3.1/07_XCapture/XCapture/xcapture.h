#pragma once

#include <QtWidgets/QWidget>
#include <QTimer>
#include <QTime>
#include "ui_xcapture.h"
#include "XVideoThread.h"
#include "XAudioThread.h"
#include "XVideoWriter.h"

#define FPS 21  // 0< fps <=21


class XCapture : public QWidget
{
    Q_OBJECT

signals:
	void CaptureScreened();
public slots:
	void path_select_onclicked();
	void control_btn_onclicked();
public:
	qint16 width = 0;
	qint16 height = 0;
	qint32 timer_id = 0;
	QTime time_stamp; // ms
	QString output_dir;

	void timerEvent(QTimerEvent* e);
	void closeEvent(QCloseEvent* e);
	XCapture(QWidget *parent = nullptr);
    ~XCapture();

	inline QString num_to_time(qint32 ts) {
		qint32 second = ts / 1000;
	
		return tr("%1:%2").arg(second / 60,2,10,QChar('0')).arg(second % 60, 2, 10, QChar('0'));
	};
	

private:
    Ui::XCaptureClass ui;
	XVideoThread *v_thread = nullptr;
	XAudioThread *a_thread = nullptr;
	XWriteThread *xw_thread = nullptr;
};
