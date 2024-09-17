#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "modelextend.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    ModelExtend *pmodel;
    QTableView *ptableView;


public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};
#endif // MAINWINDOW_H
