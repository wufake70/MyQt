#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
#include <QDebug>

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
    this->widgetsWidth = this->winRect.right*0.2;
    this->widgetsHeight = this->winRect.bottom*0.2;
    this->resize(this->widgetsWidth,this->widgetsHeight);

    this->pGridLayout = new QGridLayout(this);
    this->pLabel1 = new QLabel("球体半径:",this);
    this->pLabel2 = new QLabel("结果为",this);
    this->pPushButton = new QPushButton("计算",this);
    this->pLineEdit = new QLineEdit(this);

    // 网格布局
    pGridLayout->addWidget(pLabel1,0,0);
    pGridLayout->addWidget(pLabel2,1,0);
    pGridLayout->addWidget(pLineEdit,0,1);
    pGridLayout->addWidget(pPushButton,1,1);

    QWidget *pCentralWidget = new QWidget(this);
    pCentralWidget->setLayout(pGridLayout);
    setCentralWidget(pCentralWidget);

    // 关联信号和槽
//    connect(pPushButton,&QPushButton::clicked,this,&MainWindow::CalcBallVolume);
    connect(pPushButton,SIGNAL(clicked()),this,SLOT(CalcBallVolume()));
//    connect(pPushButton,SIGNAL(pressed()),this,SLOT(CalcBallVolume()));
}

void MainWindow::CalcBallVolume()
{
    double volume = (4/3)*PI*qPow(pLineEdit->text().toDouble(),3);
    pLabel2->setText(QString("结果为：")+QString::number(volume));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete pLabel1;
    delete pLabel2;
    delete pLineEdit;
    delete pPushButton;

}

