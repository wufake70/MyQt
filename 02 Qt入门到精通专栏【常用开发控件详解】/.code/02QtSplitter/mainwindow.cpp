#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 拆分窗口,pSplitter1布局方式 水平
    pSplitter1 = new QSplitter(Qt::Horizontal,0);
    pTextEdit1 = new QTextEdit("left",pSplitter1);

    // 拆分窗口 pSplitter1，pSplitter2 布局方式 垂直
    pSplitter2 = new QSplitter(Qt::Vertical,pSplitter1);
    pTextEdit2 = new QTextEdit("middle up",pSplitter2);
    pTextEdit3 = new QTextEdit("middle down",pSplitter2);

    // 拆分窗口 pSplitter1，pSplitter3 布局方式 垂直
    pSplitter3 = new QSplitter(Qt::Vertical,pSplitter1);
    pTextEdit4 = new QTextEdit("right",pSplitter3);
    pSplitter1->show();



}

MainWindow::~MainWindow()
{
    delete ui;
}

