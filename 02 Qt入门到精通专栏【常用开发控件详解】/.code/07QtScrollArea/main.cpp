#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(200,200);

    QLabel *pLabel = new QLabel();
    pLabel->setScaledContents(true);
    QImage *pImg = new QImage(":/new/img/tmd.png");
    // 映射图片
    pLabel->setPixmap(QPixmap::fromImage((pImg[0])));

    QScrollArea *pScrollArea = new QScrollArea();

    // 图片对齐方式
    pScrollArea->setAlignment(Qt::AlignCenter);
    // 滑动区域中组件 大小可变化
    pScrollArea->setWidgetResizable(true);

    // 滑动条策略
    pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    pScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    pScrollArea->setWidget(pLabel);

    QGridLayout *pGridLay = new QGridLayout(&w);
    pGridLay->addWidget(pScrollArea,0,0,1,1);

    w.setLayout(pGridLay);

    w.show();
    return a.exec();
}
