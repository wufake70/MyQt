#include "QtScreen.h"
#include <QScreen>
#include <QDesktopWidget>
#include <QPainter>
#include <QPixelFormat>
#include <QDebug>


QtScreen::QtScreen(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	file.setFileName(path);
	file.open(QIODevice::ReadWrite);
	startTimer(25);


}


void QtScreen::timerEvent(QTimerEvent * e)
{
	update();
}

void QtScreen::paintEvent(QPaintEvent * e)
{
	static QScreen *pScreen = NULL;
	if (!pScreen)
	{
		pScreen = QGuiApplication::primaryScreen();
	}
	// 抓取屏幕
	QPixmap pix = pScreen->grabWindow(QApplication::desktop()->winId());
	//pix.toImage().bits(); // 返回指向第一个像素数据的指针
	QImage::Format fmt = pix.toImage().format();
	
	qint32 size = pix.toImage().sizeInBytes();

	if (fmt != QImage::Format_RGBA8888)
	{
		pix.toImage().toPixelFormat(QImage::Format_RGBA8888);
		size = pix.toImage().sizeInBytes();
	}
	file.write(QByteArray((char*)pix.toImage().bits() , size));

	timestamp -= 25;
	static int fps=0;
	qDebug().noquote() << fps++ << " ";
	if (!timestamp) close();

	//在程序窗口绘制 整个屏幕
	//QPainter painter;
	//painter.begin(this);
	//painter.drawImage(QPoint(0, 0), pix.toImage());
	//painter.end();
}

void QtScreen::closeEvent(QCloseEvent * e)
{
	file.close();
	QWidget::closeEvent(e);
}
