#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    pmodel = new QDirModel(this); // 磁盘数据模型
    ptreeView = new QTreeView(this); // 树视图
    plistView = new QListView(this); // 列表视图
    ptableView = new QTableView(this); //
    ptreeView->setModel(pmodel);
    plistView->setModel(pmodel);
    ptableView->setModel(pmodel);

    ptreeView->setSelectionMode(QAbstractItemView::MultiSelection);
    plistView->setSelectionModel(ptreeView->selectionModel());
    ptableView->setSelectionModel(ptreeView->selectionModel());

    QObject::connect(ptreeView,SIGNAL(doubleClicked(const QModelIndex &)),
                     plistView,SLOT(setRootIndex(const QModelIndex &)));
    QObject::connect(ptreeView,SIGNAL(doubleClicked(const QModelIndex &)),
                     ptableView,SLOT(setRootIndex(const QModelIndex &)));

    psplitter = new QSplitter();
    psplitter->addWidget(ptreeView);
    psplitter->addWidget(plistView);
    psplitter->addWidget(ptableView);

    psplitter->show();
}

MainWindow::~MainWindow()
{
    delete ptreeView;
    delete plistView;
    delete ptableView;

    delete pmodel;
    delete psplitter;


}

