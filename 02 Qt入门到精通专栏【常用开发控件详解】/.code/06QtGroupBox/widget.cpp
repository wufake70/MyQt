#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    pGridLay = new QGridLayout(this);
    // 组合框1 单选框
    pGroupBox1 = new QGroupBox("组合框1-单选框",this);
    pVBoxLay1 = new QVBoxLayout();
    pRadioBtn1 = new QRadioButton("Radio1");
    pRadioBtn2 = new QRadioButton("Radio2");
    pRadioBtn3 = new QRadioButton("Radio3");
    pRadioBtn4 = new QRadioButton("Radio4");
    pVBoxLay1->addWidget(pRadioBtn1);
    pVBoxLay1->addWidget(pRadioBtn2);
    pVBoxLay1->addWidget(pRadioBtn3);
    pVBoxLay1->addWidget(pRadioBtn4);
    pGroupBox1->setLayout(pVBoxLay1);
    pGroupBox1->setSizePolicy(QSizePolicy::Policy::Fixed,QSizePolicy::Policy::Fixed);
    pGridLay->addWidget(pGroupBox1,0,0,1,1);

    // 组合框2 复选框
    pGroupBox2 = new QGroupBox("组合框2-复选框",this);
    pVBoxLay2 = new QVBoxLayout();
    pHBoxLay1 = new QHBoxLayout();
    pCheckBtn1 = new QCheckBox("all select");
    pCheckBtn2 = new QCheckBox("Check2");
    pCheckBtn3 = new QCheckBox("Check3");
    pCheckBtn4 = new QCheckBox("Check4");
    pVBoxLay2->addWidget(pCheckBtn1);
    pVBoxLay2->addWidget(pCheckBtn2);
    pVBoxLay2->addWidget(pCheckBtn3);
    pVBoxLay2->addWidget(pCheckBtn4);
//    pGroupBox2->setLayout(pVBoxLay2); // 组合框 垂直布局
    pHBoxLay1->addWidget(pCheckBtn1);
    pHBoxLay1->addWidget(pCheckBtn2);
    pHBoxLay1->addWidget(pCheckBtn3);
    pHBoxLay1->addWidget(pCheckBtn4);
    pGroupBox2->setLayout(pHBoxLay1); // 水平布局
    pGroupBox2->setSizePolicy(QSizePolicy::Policy::Fixed,QSizePolicy::Policy::Fixed);
    pGroupBox2->setCheckable(true); // 是否可选
    pGridLay->addWidget(pGroupBox2,0,2,1,1);
    // 全选/全不选
    connect(pCheckBtn1,SIGNAL(stateChanged(int)),this,SLOT(clickGroup2(int)));

    // 组合框3 hybrid
}

Widget::~Widget()
{
}

void Widget::clickGroup2(int state)
{
    switch (state) {
        case Qt::Checked:
        pCheckBtn1->setChecked(true);
        pCheckBtn2->setChecked(true);
        pCheckBtn3->setChecked(true);
        pCheckBtn4->setChecked(true);
        break;
    case Qt::Unchecked:
        pCheckBtn1->setChecked(false);
        pCheckBtn2->setChecked(false);
        pCheckBtn3->setChecked(false);
        pCheckBtn4->setChecked(false);
        break;
    }

}

