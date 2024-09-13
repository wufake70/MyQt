#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    pgridLay = new QGridLayout(this);
    ppushBtn = new QPushButton("select font",this);
    plineEdit = new QLineEdit("Web安全学习笔记",this);
    plineEdit->setReadOnly(true);

    pgridLay->addWidget(plineEdit,0,0,1,1);
    pgridLay->addWidget(ppushBtn,0,1,1,1);


    setLayout(pgridLay);

    connect(ppushBtn,SIGNAL(clicked()),this,SLOT(clickColorBtn()));

}
void Dialog::clickColorBtn()
{
    bool isbool;
    QFont font = plineEdit->font();
    font = QFontDialog::getFont(&isbool,font,plineEdit);
    if(isbool)
    {
        plineEdit->setFont(font);
//        font
        qDebug().noquote() << plineEdit->width() << " " << plineEdit->text().length();

        resize(sizeHint());

    }
}
Dialog::~Dialog()
{
}

