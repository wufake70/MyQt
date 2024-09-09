#include "mainwindow.h"
#include <windows.h>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    pPbtn1 = new QPushButton("push btn1",this);
    pPbtn2 = new QPushButton("push btn2",this);
    pPbtn2->setGeometry(pPbtn1->width(),0,pPbtn2->width(),pPbtn2->height());
    connect(pPbtn1,SIGNAL(clicked()),this,SLOT(ClickPbtn1()));
    connect(pPbtn2,SIGNAL(clicked()),this,SLOT(ClickPbtn2()));
}

MainWindow::~MainWindow()
{
    delete pPbtn1;
    delete pPbtn2;
}


void MainWindow::ClickPbtn1()
{
    QMessageBox::information(0,"tips",pPbtn1->text()+" clicked",0);
}

void MainWindow::ClickPbtn2()
{
    QMessageBox::information(0,"tips",pPbtn2->text()+" clicked",0);
}
