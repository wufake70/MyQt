#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(QWidget *parent,QString winTitle)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)  //    给私有成员赋初值
{
    // 获取分辨率
    GetWindowRect(GetDesktopWindow(),&this->winRect);

    ui->setupUi(this);
    this->setWindowTitle((QString&)winTitle);
    this->widgetsWidth = this->winRect.right*0.4;
    this->widgetsHeight = this->winRect.bottom*0.4;
    this->resize(this->widgetsWidth,this->widgetsHeight);
    // 标签赋值
//    this->qLabel.setText("你******好******世******界");
//    this->qLabel.setParent(this);
    this->qLabelPtr = new QLabel("你******好******Q******t",this);
    // 设置标签的坐标、宽高
    this->qLabelPtr->setGeometry(0,0,
                                 this->widgetsWidth*0.7,
                                 40);
    // 设置标签样式
    this->qLabelPtr->setStyleSheet("background:black;color:cyan;");
    this->qLabelPtr->setFont(QFont("隶属",20));


}

MainWindow::~MainWindow()
{
    delete ui;
}

