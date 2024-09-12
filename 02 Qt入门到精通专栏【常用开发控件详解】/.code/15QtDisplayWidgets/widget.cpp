#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    TestLabel();
    TestTextBrowser();
    TestProcessBar();
}

void Widget::clickTestProcessBar()
{
    while(ui->progressBar->value()!=100)
    {
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
}

void Widget::TestProcessBar()
{
    ui->progressBar->setValue(0);
    ui->progressBar->setRange(0,100);
    connect(ui->testProcessBar,SIGNAL(clicked()),this,SLOT(clickTestProcessBar()));
}

void Widget::TestTextBrowser()
{
    QFile file(":/new/prefix1/main.cpp");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(0,"error","file open fail.");
    }


    ui->textBrowser->setText(QString(file.readAll()));
}

void Widget::TestLabel()
{
    QImage img;
    if(!img.load(":/new/prefix1/debug.png"))
    {
        qDebug().noquote() << "load img error.";
    }
    ui->labelimg->setPixmap(QPixmap::fromImage(img));
    ui->labelimg->setFixedSize(img.size());
}

Widget::~Widget()
{
    delete ui;
}

