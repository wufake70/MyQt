#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton> // 命令按钮

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QPushButton *pPbtn1;
    QPushButton *pPbtn2;

private slots:
    void ClickPbtn1();
    void ClickPbtn2();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
