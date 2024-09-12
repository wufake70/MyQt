#include "dialog.h"
#include <QtDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    pgridLay = new QGridLayout();
    plabel1 = new QLabel("file path:",this);
    plabel2 = new QLabel("file size:",this);
    plineEdit1 = new MyQLineEdit(this);
    plineEdit1->setReadOnly(true);
    plineEdit2 = new MyQLineEdit(this);
    plineEdit2->setReadOnly(true);
    ppushBtn = new QPushButton("select...",this);
    plabel1->resize(plabel1->width()*2,
                    plabel1->height());

    pgridLay->addWidget(plabel1,0,0,1,1);
    pgridLay->addWidget(plabel2,1,0,1,1);
    pgridLay->addWidget(plineEdit1,0,1,1,2);
    pgridLay->addWidget(plineEdit2,1,1,1,1);
    pgridLay->addWidget(ppushBtn,0,4,1,1);
    pgridLay->setColumnMinimumWidth(2,width()*0.1);


    this->setLayout(pgridLay);
    connect(ppushBtn,SIGNAL(clicked()),this,
            SLOT(clickSelectFileBtn()));

}

void Dialog::clickSelectFileBtn()
{
    QString str;
    str = QFileDialog::getOpenFileName(this,tr("select file"),
                                       "/",tr("*"));
    plineEdit1->setText(str);
    pfile = new QFile(str);
    plineEdit2->setText(QString::number(pfile->size())+"(B)["+\
                        (pfile->size()<(1024*1024)?\
                             QString(""):\
                             QString::number\
                             ((double)pfile->size()/(1024*1024)))\
                        +"(Mb)]");

}

// 重写 QLineEdit类的mouseMoveEvent事件回调函数，
void MyQLineEdit::mouseMoveEvent(QMouseEvent *event)
{
        static uchar flag=0;
//        qDebug() << event->type() << QString::number(flag++);
        if(flag++>=0x80)
        {
            QToolTip::showText(mapToGlobal(QPoint(0, 10)), this->text());
            flag=0;
        }
}

void MyQLineEdit::leaveEvent(QEvent *event)
{

    if(event->type()==QEvent::Enter) // 鼠标移出小部件
    {
        QToolTip::hideText();
    }
}

Dialog::~Dialog()
{
}

