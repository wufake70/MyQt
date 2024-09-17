#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDirModel>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QSplitter>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QDirModel *pmodel;
    QTreeView *ptreeView;
    QListView *plistView;
    QTableView *ptableView;

    QSplitter *psplitter;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
