#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    pgridLay = new QGridLayout(this);
    ppushBtn = new QPushButton("select color",this);
    pframe = new QFrame(this);
    pframe->setFrameShape(QFrame::Box);
    pframe->setAutoFillBackground(true);

    pgridLay->addWidget(ppushBtn,0,0,1,1);
    pgridLay->addWidget(pframe,1,0,1,1);
    pgridLay->addWidget(new QFrame(),2,0,1,1);


    setLayout(pgridLay);

    connect(ppushBtn,SIGNAL(clicked()),this,SLOT(clickColorBtn()));

}
void Dialog::clickColorBtn()
{
    QColor color = QColorDialog::getColor();
    if(color.isValid())
    {
        pframe->setPalette(QPalette(color));
    }
}

Dialog::~Dialog()
{
}

