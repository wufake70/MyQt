#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建窗口对象
    MainWindow w(nullptr,"hello qt");
    w.show();


    return a.exec();
}
