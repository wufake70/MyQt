#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtScreen.h"
#include <QFile>

class QtScreen : public QWidget
{
    Q_OBJECT

public:
    QtScreen(QWidget *parent = Q_NULLPTR);
	void timerEvent(QTimerEvent* e);
	void paintEvent(QPaintEvent* e);
	void closeEvent(QCloseEvent* e);
	QFile file;
	QString path="./screen.rgb";
	qint32 timestamp = 1000 * 5;


private:
    Ui::QtScreenClass ui;
};
