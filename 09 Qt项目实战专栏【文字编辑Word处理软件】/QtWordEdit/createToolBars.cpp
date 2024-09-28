#include "mainwindow.h"


void MainWindow::createToolBars()
{
    // 文件
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(printAct);

    // 编辑
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->addSeparator();
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
    // 格式
    formatToolBar = addToolBar(tr("Format"));
    formatToolBar->addAction(boldAct);
    formatToolBar->addAction(italicAct);
    formatToolBar->addAction(underlineAct);
    formatToolBar->addSeparator();
    formatToolBar->addAction(leftAlignAct);
    formatToolBar->addAction(centerAlignAct);
    formatToolBar->addAction(rightAlignAct);
    formatToolBar->addAction(justifyAlignAct);
    formatToolBar->addSeparator();
    formatToolBar->addAction(colorAct);

    // 组合工具栏
    addToolBarBreak(Qt::TopToolBarArea);
    comboToolBar = addToolBar(tr("组合选择"));
    comboListStyle = new QComboBox();
    comboToolBar->addWidget(comboListStyle);
    comboListStyle->addItem("列表格式 none");
    comboListStyle->addItem("实心圆圈 ●");
    comboListStyle->addItem("空心圆 ○");
    comboListStyle->addItem("实心正方形 ■");
    comboListStyle->addItem("十进制值 1-∞");
    comboListStyle->addItem("小写拉丁字符 a-z");
    comboListStyle->addItem("大写拉丁字符 A-A");
    comboListStyle->addItem("小写罗马数字 ⅰ-ⅹ");
    comboListStyle->addItem("大写罗马数字Ⅰ-Ⅹ");
    comboListStyle->setStatusTip("列表格式");
    connect(comboListStyle,SIGNAL(activated(int)),this,
            SLOT(textListStyle(int)));

    comboFont = new QFontComboBox();
    comboToolBar->addWidget(comboFont);
    comboFont->setStatusTip("更改字体");
    comboFont->setCurrentFont(QFont("宋体"));
    connect(comboFont,SIGNAL(activated(QString)),this,
            SLOT(textFamily(QString)));

    comboSize = new QComboBox();
    comboToolBar->addWidget(comboSize);
    comboSize->setEditable(true);
    comboSize->setStatusTip("字体大小");

    QFontDatabase fontdb;
    for(int i=5;i<fontdb.standardSizes().length()+50;i++)
    {
        comboSize->addItem("字号: "+QString::number(i));
    }
    connect(comboSize,SIGNAL(activated(QString)),this,
            SLOT(textSize(QString)));
    comboSize->setCurrentIndex(comboSize->findText(
                                   "字号: "+QString::number(11)));
}
