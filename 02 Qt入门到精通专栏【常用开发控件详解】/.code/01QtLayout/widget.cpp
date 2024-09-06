#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    pBtn1 = new QPushButton(this);
    pBtn1->setText("顶部菜单栏选项");
//    pBtn1->setFixedWidth(60);  // 固定按钮宽度
    pBtn1->setFixedHeight(60);  // 固定按钮高度
    // 按钮大小策略，若设定了固定宽度、高度则无效
    pBtn1->setSizePolicy(QSizePolicy::Expanding,\
                         QSizePolicy::Expanding);     // Expanding 随主窗口变化，Fixed 固定不变

    pBtn2 = new QPushButton(this);
    pBtn2->setText("左侧边栏");
    pBtn2->setFixedWidth(60);
    pBtn2->setSizePolicy(QSizePolicy::Fixed,\
                         QSizePolicy::Expanding);
    pBtn3 = new QPushButton(this);
    pBtn3->setText("右侧边栏");
    pBtn3->setFixedWidth(60);
    pBtn3->setSizePolicy(QSizePolicy::Fixed,\
                         QSizePolicy::Expanding);

    pBtn4 = new QPushButton(this);
    pBtn4->setText("底部边栏");
    pBtn4->setFixedHeight(60);
    pBtn4->setSizePolicy(QSizePolicy::Expanding,\
                         QSizePolicy::Expanding);


    /*
        addwidget（参数1，参数2，参数3，参数4，参数5，参数6）
        1：我要插入的子布局对象    2：插入的开始行
        3：插入的开始列         4：占用的行数
        5：占用的列数         6：指定对齐方式
     */
    pGridLay = new QGridLayout(this);
    pGridLay->addWidget(pBtn1,0,0,1,3);
    pGridLay->addWidget(pBtn2,1,0);
    pGridLay->addWidget(pBtn3,1,2);
    pGridLay->addWidget(pBtn4,2,0,1,3);

    // 设置样式内部边距 参数顺序 left、top、right、bottom
    pGridLay->setContentsMargins(10,0,10,0);
    // 外边距
    pGridLay->setMargin(50);
    // 间隔为零
    pGridLay->setSpacing(0);
    setLayout(pGridLay);
}

Widget::~Widget()
{
}

