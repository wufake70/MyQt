#include "xcapture.h"
#include <QDebug>
#include <QScreen>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>

void XCapture::timerEvent(QTimerEvent * e)
{
	ui.timer_show->setText(num_to_time(time_stamp.elapsed()));
	emit v_thread->CaptureScreened();
	emit a_thread->CaptureAudioed();

}
void XCapture::closeEvent(QCloseEvent* e)
{
	if (v_thread || a_thread || xw_thread) e->ignore();
	if (XWriteThread::Get()->isRunning()) e->ignore();
}

XCapture::XCapture(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);

	QScreen *pScreen = QGuiApplication::primaryScreen();
	width = pScreen->geometry().width();
	height = pScreen->geometry().height();
	ui.resolution_show->setText(QString::number(width) + 
								tr("x") + QString::number(height));

	ui.path_edit->setReadOnly(true);
	QString homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
	homePath += "/XCapture";
	QDir homeDir(homePath);
	if (!homeDir.exists())
	{
		homeDir.mkdir(".");
	}
	ui.path_edit->setText(homePath);
	output_dir = homePath;
}

XCapture::~XCapture()
{

}

void XCapture::path_select_onclicked()
{
	QString tmp= QFileDialog::getExistingDirectory(nullptr, 
						"Select Folder", output_dir);
	if (!tmp.isEmpty())output_dir = tmp;
	ui.path_edit->setText(output_dir);
}

void XCapture::control_btn_onclicked()
{
	static bool is_recording = true;
	ui.timer_show->setText(num_to_time(time_stamp.elapsed()));
	if (is_recording)
	{
		timer_id = startTimer(1000/FPS); 
		time_stamp.restart();
		ui.control_btn->setText(tr(u8"停止"));
		is_recording = false;
		v_thread = XVideoThread::Get();
		a_thread = XAudioThread::Get();
		xw_thread = XWriteThread::Get();

		v_thread->init(FPS,width,height,output_dir);
		a_thread->init(output_dir);
		xw_thread->init(FPS-1,width,height, output_dir);
		if (v_thread->is_init&&
			a_thread->is_init&&
			xw_thread->is_init)
		{
			v_thread->start();
			a_thread->start();
			xw_thread->start();
		}
	}
	else {
		killTimer(timer_id);

		emit v_thread->Quited();
		emit a_thread->Quited();
		emit xw_thread->Quited();
		v_thread = nullptr;
		a_thread = nullptr;
		xw_thread = nullptr;

		ui.control_btn->setText(tr(u8"开始"));
		is_recording = true;
	}

}