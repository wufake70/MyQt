#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel> // 导入标签头文件
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout> // 网格布局
#include <windows.h>

#define PI 3.1415926

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
    RECT winRect;
    ULONG widgetsWidth;
    ULONG widgetsHeight;

    QLabel *pLabel1,*pLabel2;
    QLineEdit *pLineEdit;
    QPushButton *pPushButton;
    QGridLayout *pGridLayout;   // 网格布局
    QWidget *pCentralWidget;    // 中心组件

private slots:  // 槽函数
    void CalcBallVolume();


};
#endif // MAINWINDOW_H
