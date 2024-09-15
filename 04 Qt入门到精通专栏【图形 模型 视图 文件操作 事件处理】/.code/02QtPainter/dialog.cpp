#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QWidget(parent)
{
    pHBoxLay = new QHBoxLayout(this);
    ppaintArea = new PaintArea();
    pgridLay = new QGridLayout(this);

    plabel = new QLabel("选择绘制图形:",this);
    pComboBox = new QComboBox(this);
    pComboBox->addItem("Line",PaintArea::Line);
    pComboBox->addItem("Rectangle",PaintArea::Rectangle);

    pgridLay->addWidget(plabel,0,0,1,1);
    pgridLay->addWidget(pComboBox,0,1,1,1);
    pgridLay->setColumnStretch(0,0);
    pgridLay->setColumnStretch(1,0);
    pgridLay->setColumnStretch(2,1);

    pHBoxLay->addWidget(ppaintArea,1);
    pHBoxLay->addLayout(pgridLay,0);
    setLayout(pHBoxLay);

    resize(size());

    connect(pComboBox,SIGNAL(activated(int)),this,SLOT(selectDrawShape(int)));


}

void Dialog::selectDrawShape(int index)
{
    PaintArea::Shape shape = PaintArea::Shape(pComboBox->itemData(index,Qt::UserRole).toInt());
    ppaintArea->setShape(shape);
}


Dialog::~Dialog()
{
}

