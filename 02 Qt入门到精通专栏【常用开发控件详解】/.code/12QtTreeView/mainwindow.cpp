#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitTreeViewFunc();
}

void MainWindow::InitTreeViewFunc()
{
    pStandardItemModel = new QStandardItemModel(ui->treeView);
    // 表头
    pStandardItemModel->setHorizontalHeaderLabels(QStringList()<<"serial"<<"name"<<"description");
    ui->treeView->setModel(pStandardItemModel);

    // 添加一级节点
    QList<QStandardItem*> item1;
    QStandardItem *item1_serial = new QStandardItem(QString::number(1));
    QStandardItem *item1_name = new QStandardItem("一级目录");
    item1.append({item1_serial,item1_name});
//    pStandardItemModel->appendRow(item1);

    // 一级目录下二级节点
    QList<QStandardItem*> item1_1;
    QStandardItem *item1_1_serial = new QStandardItem(QString::number(1));
    QStandardItem *item1_1_name = new QStandardItem("二级目录");
    QStandardItem *item1_1_description = new QStandardItem("描述");
    item1_1.append({item1_1_serial,item1_1_name,item1_1_description});
    item1_serial->appendRow(item1_1); // 下一层目录要放在当前节点第一个item
    pStandardItemModel->appendRow(item1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

