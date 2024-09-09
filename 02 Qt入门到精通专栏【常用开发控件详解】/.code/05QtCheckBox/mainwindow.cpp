#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    pCheckBox = new QCheckBox(this);
    pCheckBox->setTristate();   // 加上半选模式
    pCheckBox->setText("复选框");

    connect(pCheckBox,SIGNAL(stateChanged(int)),this,SLOT(ClickCheckBox(int)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::ClickCheckBox(int state)
{
    switch (state) {
    case Qt::Checked:
        pCheckBox->setText("Checked");
        break;
    case Qt::Unchecked:
        pCheckBox->setText("UnChecked");
        break;
    case Qt::PartiallyChecked:
        pCheckBox->setText("Part Checked");
        break;
    }
}

