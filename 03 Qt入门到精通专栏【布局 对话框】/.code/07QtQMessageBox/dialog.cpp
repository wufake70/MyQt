#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    pGridLay = new QGridLayout(this);
    pQuesMboxBtn= new QPushButton("QuestionMsg",this);
    pInfoMboxBtn= new QPushButton("InformationMsg",this);
    pWarnMboxBtn= new QPushButton("WarnMsg",this);
    pErrorMboxBtn= new QPushButton("ErrorMsg",this);
    pAboutMboxBtn= new QPushButton("AboutMsg",this);
    pAboutQtMboxBtn= new QPushButton("AboutQtMsg",this);

    pGridLay->addWidget(pQuesMboxBtn,0,0);
    pGridLay->addWidget(pInfoMboxBtn,1,0);
    pGridLay->addWidget(pWarnMboxBtn,2,0);
    pGridLay->addWidget(pErrorMboxBtn,3,0);
    pGridLay->addWidget(pAboutMboxBtn,4,0);
    pGridLay->addWidget(pAboutQtMboxBtn,5,0);

    pScreen = QApplication::primaryScreen();

    setLayout(pGridLay);
    connect(pQuesMboxBtn,SIGNAL(clicked()),this,SLOT(clickQuesBtn()));
    connect(pInfoMboxBtn,SIGNAL(clicked()),this,SLOT(clickInfoBtn()));
    connect(pWarnMboxBtn,SIGNAL(clicked()),this,SLOT(clickWarnBtn()));
    connect(pErrorMboxBtn,SIGNAL(clicked()),this,SLOT(clickErrorBtn()));
    connect(pAboutMboxBtn,SIGNAL(clicked()),this,SLOT(clickAboutBtn()));
    connect(pAboutQtMboxBtn,SIGNAL(clicked()),this,SLOT(clickAboutQtBtn()));



}


void Dialog::clickQuesBtn()
{
    QPoint pos(pScreen->geometry().width()/2,
               pScreen->geometry().height()*0.08);
    switch(QMessageBox::question(this,"tip","question",
                          QMessageBox::Ok|QMessageBox::Cancel,
                          QMessageBox::Cancel))
    {
    case QMessageBox::Ok:
        QToolTip::showText(pos,"OK",this);
        break;
    case QMessageBox::Cancel:
        QToolTip::showText(pos,"Cannel");
        break;
    }

}
void Dialog::clickInfoBtn()
{
    QMessageBox::information(this,"infoMsg","....",
                             QMessageBox::Ok);

}
void Dialog::clickWarnBtn()
{
    QMessageBox::warning(this,"warn","....",QMessageBox::Ok);
}
void Dialog::clickErrorBtn()
{
    QMessageBox::critical(this,"Error","....");
}
void Dialog::clickAboutBtn()
{
    QMessageBox::about(this,"About","....");
}
void Dialog::clickAboutQtBtn()
{
    QMessageBox::aboutQt(this,"AboutQt");

}

Dialog::~Dialog()
{
}

