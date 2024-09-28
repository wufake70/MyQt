#include "mainwindow.h"


void MainWindow::createMenus()
{
    // 菜单栏使用的是 MainWindow QMenuBar对象
    menuBar()->setStyleSheet("background-color:  rgb(240,240,240);");
    // 文件菜单
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(newAct); // 添加操作
    fileMenu->addAction(openAct);
    fileMenu->addSeparator(); // 添加分隔符
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator(); // 添加分隔符
    fileMenu->addAction(printAct);
    fileMenu->addAction(printPreviewAct);
    fileMenu->addSeparator(); // 添加分隔符
    fileMenu->addAction(exitAct);

    // 编辑菜单
    editMenu = menuBar()->addMenu(tr("Eidt"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator(); // 添加分隔符
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator(); // 添加分隔符

    // 格式菜单
    formatMenu = menuBar()->addMenu(tr("Format"));
    fontMenu = formatMenu->addMenu(tr("Font")); // 字体格式
    fontMenu->addAction(boldAct);
    fontMenu->addAction(italicAct);
    fontMenu->addAction(underlineAct);

    alignMenu = formatMenu->addMenu(tr("Align")); // 对齐方式
    alignMenu->addAction(leftAlignAct);
    alignMenu->addAction(rightAlignAct);
    alignMenu->addAction(centerAlignAct);
    alignMenu->addAction(justifyAlignAct);

    formatMenu->addAction(colorAct);

    // 窗口菜单--多文档窗口菜单 单独使用一个函数来更新
    windowMenu = menuBar()->addMenu(tr("Windows"));
    updateWindowMenu();
    connect(windowMenu,SIGNAL(aboutToShow()),this, //aboutToShow
            SLOT(updateWindowMenu()));
    windowMenu->addSeparator();

    // 帮助菜单
    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutQtAct);

    connect(menuBar(),SIGNAL(aboutToShow()),this, //aboutToShow
            SLOT(updateMenus()));
}
