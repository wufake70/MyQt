#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(200,300);
    pLedit1 = new QLineEdit();
    pLedit2 = new QLineEdit();
    pLedit3 = new QLineEdit();
    pLedit4 = new QLineEdit();

    pFormLay = new QFormLayout(this);
    pFormLay->addRow("学校:",pLedit1);
    pFormLay->addRow("学院:",pLedit2);
    pFormLay->addRow("专业:",pLedit3);
    pFormLay->addRow("姓名:",pLedit4);

    pFormLay->setSpacing(5);
    // 表单中标签在编辑框上面
//    pFormLay->setRowWrapPolicy(QFormLayout::WrapAllRows);
    // 标签显示在 编辑框左边
    pFormLay->setRowWrapPolicy(QFormLayout::WrapLongRows);
    pFormLay->setAlignment(Qt::AlignLeft);
    pFormLay->setMargin(15);
}

Widget::~Widget()
{
}

