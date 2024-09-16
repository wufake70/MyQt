#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    pSence = new QGraphicsScene(this);

    pImg = new QPixmap(":/new/prefix1/test.png");
    // 场景的范围,
    pSence->setSceneRect(-pImg->width()/2,pImg->height()/2,// 左上角
                         pImg->width(),pImg->height());

    pItem = new PixelItem(pImg);
    pSence->addItem(pItem);
    pItem->setPos(0,0);
//    pSence

    pView = new QGraphicsView;
    pView->setScene(pSence);
    pView->setMinimumSize(pImg->width(),pImg->height());

    pControlFreme = new QFrame(this);
    InitControlFrame();

    pHBoxLay = new QHBoxLayout(this);
    pHBoxLay->addWidget(pView);
    pHBoxLay->addWidget(pControlFreme);

    setLayout(pHBoxLay);
}


void Widget::InitControlFrame()
{
    pVBoxLay = new QVBoxLayout(pControlFreme);

    pGroupBox1 = new QGroupBox(tr("图片旋转"),pControlFreme);
    pSlider1 = new MyQSlider(Qt::Horizontal,pGroupBox1);
    pSlider1->setRange(0,360);
    pSlider1->setToolTip("0");
    connect(pSlider1,SIGNAL(valueChanged(int)),this,SLOT(RotateImg(int)));
    pGroupBox1VBoxLay = new QVBoxLayout(pGroupBox1);
    pGroupBox1VBoxLay->addWidget(pSlider1);
    pGroupBox1->setLayout(pGroupBox1VBoxLay);


    pGroupBox2 = new QGroupBox(tr("图片缩放"),pControlFreme);
    pSlider2 = new MyQSlider(Qt::Horizontal,pGroupBox2);
    pSlider2->setValue(10);
    pSlider2->setRange(1,100);
    pSlider2->setToolTip("1");
    pGroupBox2VBoxLay = new QVBoxLayout(pGroupBox2);
    pGroupBox2VBoxLay->addWidget(pSlider2);
    pGroupBox2->setLayout(pGroupBox2VBoxLay);
    connect(pSlider2,SIGNAL(valueChanged(int)),this,SLOT(ScaleImg(int)));

    pGroupBox3 = new QGroupBox(tr("图片倾斜"),pControlFreme);
    pSlider3 = new MyQSlider(Qt::Horizontal,pGroupBox3);
    pSlider3->setValue(0);
    pSlider3->setRange(-10,10);
    pGroupBox3VBoxLay = new QVBoxLayout(pGroupBox3);
    pGroupBox3VBoxLay->addWidget(pSlider3);
    pGroupBox3->setLayout(pGroupBox3VBoxLay);
    connect(pSlider3,SIGNAL(valueChanged(int)),this,SLOT(TiltImg(int)));

    pVBoxLay->addWidget(pGroupBox1);
    pVBoxLay->addWidget(pGroupBox2);
    pVBoxLay->addWidget(pGroupBox3);

    pControlFreme->setLayout(pVBoxLay);
}

// 旋转规则
void Widget::RotateImg(int offset)
{
    static qreal base=0;

    QToolTip::hideText();
    pView->rotate(-base+offset);
    pSlider1->setToolTip(QString::number(offset));
//    QToolTip::showText(pSlider1->mousePos,QString::number(offset));
    QToolTip::showText(pSlider1->mapToGlobal(QPoint(pSlider1->rect().left(),
                                                    pSlider1->rect().bottom())),
                       QString::number(offset));
    base = offset;
}

// 缩放规则
void Widget::ScaleImg(int offset)
{
    static qreal base=1;

    QToolTip::hideText();
    pView->scale((offset/base)/10,(offset/base)/10);
    pSlider2->setToolTip(QString::number((qreal)offset/10));
//    QToolTip::showText(pSlider1->mousePos,QString::number(offset));
    QToolTip::showText(pSlider2->mapToGlobal(QPoint(pSlider2->rect().left(),
                                                    pSlider2->rect().bottom())),
                       QString::number((qreal)offset/10));
    base *= (offset/base)/10;
}
void Widget::TiltImg(int offset)
{
    static qreal base=0;

    QToolTip::hideText();
    pView->shear(-base+offset,0);
//    pView->tile
    pSlider3->setToolTip(QString::number(offset));
//    QToolTip::showText(pSlider1->mousePos,QString::number(offset));
    QToolTip::showText(pSlider3->mapToGlobal(QPoint(pSlider3->rect().left(),
                                                    pSlider3->rect().bottom())),
                       QString::number(offset));
    base = offset;
}

void MyQSlider::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug() << event->globalPos();
    mousePos = event->globalPos();
    QSlider::mouseMoveEvent(event); // 将事件传给父类

}

Widget::~Widget()
{
}

