#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->frame->setStyleSheet("background-color:yellow;");
    ui->frame->setFrameShape(QFrame::Box);
    ui->frame_2->setStyleSheet("background-color:cyan;");
}

Widget::~Widget()
{
    delete ui;
}

