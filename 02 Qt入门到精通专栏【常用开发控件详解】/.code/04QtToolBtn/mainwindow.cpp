#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pToolBar = new QToolBar(this);
    pToolFileBtn = new QToolButton();
    pToolFileBtn->setText("文件(F)");
    pToolEidtBtn = new QToolButton();
    pToolEidtBtn->setText("编辑(E)");
    pToolBuildBtn = new QToolButton();
    pToolBuildBtn->setText("构建(B)");
    pToolDebugBtn = new QToolButton();
    pToolDebugBtn->setText("调试(D)");
    pToolAnalyzeBtn = new QToolButton();
    pToolAnalyzeBtn->setText("分析(A)");
    pToolToolBtn = new QToolButton();
    pToolToolBtn->setText("工具(T)");
    pToolControlBtn = new QToolButton();
    pToolControlBtn->setText("编辑(W)");
    pToolHelpBtn = new QToolButton();
    pToolHelpBtn->setText("编辑(H)");

    pToolBar->addWidget(pToolFileBtn);
    pToolBar->addWidget(pToolEidtBtn);
    pToolBar->addWidget(pToolBuildBtn);
    pToolBar->addWidget(pToolDebugBtn);
    pToolBar->addWidget(pToolAnalyzeBtn);
    pToolBar->addWidget(pToolToolBtn);
    pToolBar->addWidget(pToolControlBtn);
    pToolBar->addWidget(pToolHelpBtn);

    // 将工具条组件添加到主窗口
    addToolBar(pToolBar);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pToolFileBtn;
    delete pToolEidtBtn;
    delete pToolBuildBtn;
    delete pToolDebugBtn;
    delete pToolAnalyzeBtn;
    delete pToolToolBtn;
    delete pToolControlBtn;
    delete pToolHelpBtn;
}

