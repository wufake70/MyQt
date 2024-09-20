#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("左键放大/右键缩小");
    pimg = new QImage(":/new/prefix1/test.png");
    plabel = new QLabel(this);
    plabel->setPixmap(QPixmap::fromImage(*pimg));
    plabel->setAlignment(Qt::AlignCenter);
    plabel->setFixedSize(pimg->size());

    resize(pimg->size());
    plabel->installEventFilter(this);
//    plabel->removeEventFilter(this);



}

MainWindow::~MainWindow()
{
}

bool MainWindow::eventFilter(QObject *watched,QEvent *event)
{
    if(watched==plabel&&
            event->type()==QEvent::MouseButtonPress)
    {
        static double factor = 1;
        QMouseEvent *mouseEvent = (QMouseEvent*)event;
        switch(mouseEvent->button())
        {
        case Qt::LeftButton:
//                pimg;
            factor+=0.1;
            plabel->setPixmap(QPixmap::fromImage(*pimg).scaled(pimg->size().width()*factor,
                                                                pimg->size().height()*factor,
                                                               Qt::KeepAspectRatio));
            plabel->setFixedSize(pimg->size().width()*factor,
                                 pimg->size().height()*factor);

            break;

        case Qt::RightButton:
            if(factor!=0.1) factor-=0.1;
            plabel->setPixmap(QPixmap::fromImage(*pimg).scaled(pimg->size().width()*factor,
                                                                pimg->size().height()*factor,
                                                               Qt::KeepAspectRatio));
            plabel->setFixedSize(pimg->size().width()*factor,
                                 pimg->size().height()*factor);
            break;

        case Qt::MidButton:
            if(factor!=0.1) factor-=0.1;
            plabel->setPixmap(QPixmap::fromImage(*pimg).scaled(pimg->size().width()*factor,
                                                                pimg->size().height()*factor,
                                                               Qt::KeepAspectRatio));
            plabel->setFixedSize(pimg->size().width()*factor,
                                 pimg->size().height()*factor);
            break;

        }
    }

    return QMainWindow::eventFilter(watched,event);
}

