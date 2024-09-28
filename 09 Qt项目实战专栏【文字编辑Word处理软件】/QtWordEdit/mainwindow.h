#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPrintDialog>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include "textedit.h"
#include <QComboBox>
#include <QMdiArea>
#include <QSignalMapper>
#include <QAction>
#include <QApplication>
#include <QMenuBar>
#include <QToolBar>
#include <QFontComboBox>
#include <QCloseEvent>
#include <QStatusBar>
#include <QMdiSubWindow>
#include <QFileInfo>
#include <QFileDialog>
#include <QColorDialog>
#include <QMessageBox>

typedef TextEdit MyTextEdit;

class QAction; //被创建后必须将它添加到菜单和工具栏，然后将它链接到实现的action功能的槽函数
class QMenu;//QMenu为菜单，菜单QMenu是挂载在菜单栏QMenuBar（容器）上面的。
class QcomboBox; // 组合框
class QFontComboBox; //字体下拉选择框
class QMdiArea; //
class QMdiSubWindow;
class QSignalMapper;

// QAction；//被创建后必须将它添加到菜单和工具栏，然后将它链接到实现的action功能的槽函数
// QMenu；//QMenu为菜单，菜单QMenu是挂载在菜单栏QMenuBar（容器）上面的。
// QComboBox；//选项列表（组合框）
// QFontComboBox；//字体下拉列表框（不能被编辑，只是用来选择字体）
// QMdiArea；//提供一个可以同时显示多个文档容器的区域
// 大多数复杂项目软件，都是使用MDI框架，QMdiArea用于主容器当中，用于容纳多个子容器QMdiSubWindow
// QMdiSubWindow;
// QSignalMapper；//此类专门收集一系列无参信号

extern const QString icon_path;
extern const uint status_bar_time1;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void filePrint();
    void filePrintPreview();
    void printPreview(QPrinter*);

    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void about();
    void aboutQt();

    void textInitStyle();
    void updateStyleMenusStatus();
    void textBold();
    void textItalic();
    void textUnderline();
    void textAlign(QAction *a);
    void textListStyle(int styleIndex);
    void textFamily(const QString&f);
    void textSize(const QString &p);
    void textColor();
    void updateMenus(); // 更新菜单
    void updateWindowMenu(); // 更新窗口菜单
    void setActiveSubwindow(QWidget *window);
    MyTextEdit *createMyTextEdit();

private:
    void createActions();//创建菜单操作
    void createMenus();//创建菜单
    void createToolBars();//创建工具条
    void initStatusBar();//创建状态条
    void enabledText();
    void fontChanged(const QFont&f);
    void colorChanged(const QColor&c);
    void alignmentChanged(Qt::Alignment);
    MyTextEdit *getActiveMyTextEdit();
    QMdiSubWindow *findMyTextEdit(const QString&filename);
    QMdiArea *mdiArea;//多文档容器的管理器
    QSignalMapper *windowMapper;

    //定义菜单
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *fontMenu;
    QMenu *alignMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;
    //工具栏
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *formatToolBar;
    QToolBar *comboToolBar;
    QComboBox *comboListStyle;//子控件标准组合框
    QFontComboBox *comboFont;//子控件字体组合框
    QComboBox *comboSize;   //子控件：字体大小组合框
    // 菜单动作（Action）
    QAction  *newAct;
    QAction  *openAct;
    QAction  *saveAct;
    QAction  *saveAsAct;
    QAction  *printAct;
    QAction  *printPreviewAct;
    QAction  *exitAct;
    QAction  *undoAct;
    QAction  *redoAct;
    QAction  *cutAct;
    QAction  *copyAct;
    QAction  *pasteAct;
    QAction  *boldAct;
    QAction  *italicAct;
    QAction  *underlineAct;

    QActionGroup *alignStyleGrp;
    QAction  *leftAlignAct;
    QAction  *centerAlignAct;
    QAction  *rightAlignAct;
    QAction  *justifyAlignAct;
    QAction  *colorAct;

    QAction *closeAct;
    QAction *closeAllAct;
    QAction *tileWindowsAct; // 排列
    QAction *cascadeWindowAct; // 平铺
    QAction *separateAct;
    QAction *nextAct;
    QAction *previousAct;

    QAction *aboutAct;
    QAction *aboutQtAct;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
//    void mouseMoveEvent(QMouseEvent *event);
//    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
//    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *e);

};
#endif // MAINWINDOW_H
