#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel> // 导入标签头文件
#include <windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QWidget *parent,QString winTitle);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel qLabel;
    QLabel *qLabelPtr;
    RECT winRect;
    ULONG widgetsWidth;
    ULONG widgetsHeight;
};
#endif // MAINWINDOW_H
