#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    pCenterWidget = new QWidget(this);
    ppushBtn1 = new QPushButton("name  :");
    ppushBtn2 = new QPushButton("gender:");
    ppushBtn3 = new QPushButton("id    :");
    ppushBtn4 = new QPushButton("score :");

    pgridLay = new QGridLayout(pCenterWidget);
    plineEdit1 = new QLineEdit(pCenterWidget);
    plineEdit2 = new QLineEdit(pCenterWidget);
    plineEdit3 = new QLineEdit(pCenterWidget);
    plineEdit4 = new QLineEdit(pCenterWidget);
    plineEdit1->setReadOnly(true);
    plineEdit2->setReadOnly(true);
    plineEdit3->setReadOnly(true);
    plineEdit4->setReadOnly(true);

    pgridLay->addWidget(ppushBtn1,0,0,1,1);
    pgridLay->addWidget(ppushBtn2,1,0);
    pgridLay->addWidget(ppushBtn3,2,0);
    pgridLay->addWidget(ppushBtn4,3,0);

    pgridLay->addWidget(plineEdit1,0,1,1,1);
    pgridLay->addWidget(plineEdit2,1,1);
    pgridLay->addWidget(plineEdit3,2,1);
    pgridLay->addWidget(plineEdit4,3,1);

    pCenterWidget->setLayout(pgridLay);
    pCenterWidget->resize(pCenterWidget->sizeHint());

    resize(pCenterWidget->width(),
           pCenterWidget->height());

    connect(ppushBtn1,SIGNAL(clicked()),this,SLOT(clickNameBtn()));
    connect(ppushBtn2,SIGNAL(clicked()),this,SLOT(clickGenderBtn()));
    connect(ppushBtn3,SIGNAL(clicked()),this,SLOT(clickIdBtn()));
    connect(ppushBtn4,SIGNAL(clicked()),this,SLOT(clickScoreBtn()));

}

void MainWindow::clickNameBtn()
{
    bool isok;
    QString content = QInputDialog::getText(this,"tip","input your name",
                          QLineEdit::Normal,nullptr,
                          &isok);
    if(isok&&!content.isEmpty())
    {
        plineEdit1->setText(content);
    }
}

void MainWindow::clickGenderBtn()
{
    bool isok;
    QStringList genderItems;
    genderItems << "male" << "female";

    QString result = QInputDialog::getItem(this,"tip","select your gender",
                                          genderItems,0,false,&isok);
    if(isok&&!result.isEmpty())
    {
        plineEdit2->setText(result);
    }

}

void MainWindow::clickIdBtn()
{
    bool isok;
    int result = QInputDialog::getInt(this,"tip","input your student id",
                         0,-1,0x7fffffff,1,&isok);
    if(isok&&result!=0)
    {
            plineEdit3->setText(QString::number(result));
    }
}

void MainWindow::clickScoreBtn()
{
    bool isok;
    int result = QInputDialog::getInt(this,"tip","input your score",
                         0,0,100,1,&isok);
    if(isok&&result!=-1)
    {
            plineEdit4->setText(QString::number(result));
    }
}

MainWindow::~MainWindow()
{
}

