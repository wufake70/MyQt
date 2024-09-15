#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    pgridLay = new QGridLayout(this);
    plabel0 = new QLabel("pos()     :",this);
    plabel1 = new QLabel("geometry():",this);
    plabel2 = new QLabel("width()   :",this);
    plabel3 = new QLabel("height()  :",this);
    plabel4 = new QLabel("rect()    :",this);
    plabel5 = new QLabel("size()    :",this);

    plabel6 = new QLabel(this);
    plabel7 = new QLabel(this);
    plabel8 = new QLabel(this);
    plabel9 = new QLabel(this);
    plabel10 = new QLabel(this);
    plabel11 = new QLabel(this);

    pgridLay->addWidget(plabel1,0,0,Qt::AlignRight);
    pgridLay->addWidget(plabel2,1,0,Qt::AlignRight);
    pgridLay->addWidget(plabel3,2,0,Qt::AlignRight);
    pgridLay->addWidget(plabel4,3,0,Qt::AlignRight);
    pgridLay->addWidget(plabel5,4,0,Qt::AlignRight);
    pgridLay->addWidget(plabel0,5,0);
    pgridLay->addWidget(plabel6,0,1);
    pgridLay->addWidget(plabel7,1,1);
    pgridLay->addWidget(plabel8,2,1);
    pgridLay->addWidget(plabel9,3,1);
    pgridLay->addWidget(plabel10,4,1);
    pgridLay->addWidget(plabel11,5,1);

    pgridLay->setColumnStretch(0,0);
    pgridLay->setColumnStretch(1,0);
    pgridLay->setColumnStretch(2,1);
//    pgridLay->setSizeConstraint(QLayout::SetFixedSize); // 固定大小

    setLayout(pgridLay);
}

void Dialog::updata()
{
    QRect rect1 = geometry();
    QPoint point = pos();

    plabel11->setText(QString("%1,%2").arg(point.x()).arg(point.y()));

    plabel6->setText(QString("%1,%2,%3,%4").
                     arg(rect1.x()).
                     arg(rect1.y()).
                     arg(rect1.width()).
                     arg(rect1.height()));

    rect1 = rect();
    plabel7->setText(QString("%1").arg(width()));
    plabel8->setText(QString("%1").arg(height()));
    plabel8->setText(QString("%1").arg(height()));
    plabel9->setText(QString("%1,%2,%3,%4").
                     arg(rect1.x()).
                     arg(rect1.y()).
                     arg(rect1.width()).
                     arg(rect1.height()));
    plabel10->setText(QString("%1,%2").arg(size().width()).arg(size().height()));

}


void Dialog::resizeEvent(QResizeEvent *event)
{
    updata();
}
void Dialog::moveEvent(QMoveEvent *event)
{
    updata();
}


Dialog::~Dialog()
{
}

