#include "widget.h"
#include <QScreen>
#include <QLabel>
#include <QGridLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QScreen *pScreen = QApplication::primaryScreen();
//    setGeometry(pScreen->geometry().width())
    resize(pScreen->geometry().width()*0.5,
           pScreen->geometry().height()*0.5);

    pTabWidget = new QTabWidget(this);
    pTabWidget->setGeometry(width()*0.1/2,
                            height()*0.1/2,
                            width()*0.9,
                            height()*0.9);
    QGridLayout *pGridLay = new QGridLayout(pTabWidget);
    QLabel *plabel = new QLabel("process");
    pSubWidget1 = new QWidget();
    pTabWidget->addTab(pSubWidget1,"进程");   // 添加标签
    pGridLay->addWidget(plabel,0,0,1,1,Qt::AlignCenter);

    pSubWidget2 = new QWidget();
    pTabWidget->addTab(pSubWidget2,"性能");
    pSubWidget3 = new QWidget();
    pTabWidget->addTab(pSubWidget3,"服务");

    this->show();

}

Widget::~Widget()
{
}

void Widget::resizeEvent(QResizeEvent *event)
{
    pTabWidget->setGeometry(width()*0.1/2,
                            height()*0.1/2,
                            width()*0.9,
                            height()*0.9);
}

