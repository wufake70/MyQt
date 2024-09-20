#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QImage>
#include <QLabel>
#include <QEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QImage *pimg;
    QLabel *plabel;


    bool eventFilter(QObject *watched,QEvent *event);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
