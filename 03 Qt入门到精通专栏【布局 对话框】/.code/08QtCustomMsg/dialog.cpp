#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    pgridLay = new QGridLayout(this);
    plabel = new QLabel("result:",this);
    ppushuBtn = new QPushButton("test CostomMsg",this);

    pgridLay->addWidget(ppushuBtn,0,0,1,1);
    pgridLay->addWidget(plabel,1,0,1,1);

    connect(ppushuBtn,SIGNAL(clicked()),this,SLOT(testCustomMsg()));

}

void Dialog::testCustomMsg()
{
    QMessageBox customMsg;
    customMsg.setWindowTitle("test CustomMsg");

    // 添加按钮
    QPushButton *yes = customMsg.addButton("yes",QMessageBox::ActionRole);
    QPushButton *no = customMsg.addButton("no",QMessageBox::ActionRole);

    // 添加图标
    customMsg.setIconPixmap(QPixmap(":/new/prefix1/download.png"));
    customMsg.exec();

    if(customMsg.clickedButton() == yes)
    {
        plabel->setText(QString("result: ")+"yes");
    }else{
        plabel->setText(QString("result: ")+"no");
    }

}


Dialog::~Dialog()
{
}

