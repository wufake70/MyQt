#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    pmodel = new ModelExtend;
    ptableView = new QTableView();
    ptableView->setModel(pmodel);

    ptableView->resize(600,200);
    ptableView->show();
}

MainWindow::~MainWindow()
{
}

