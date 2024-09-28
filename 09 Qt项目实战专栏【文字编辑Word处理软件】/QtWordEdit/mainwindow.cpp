#include "mainwindow.h"

const QString icon_path=":/new/prefix1/png/";
const uint status_bar_time1 = 5000; // ms

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    setCentralWidget(mdiArea);
    connect(mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow *)),
            this,SLOT(updateMenus()));

    // 可以将一个信号映射到多个槽
    windowMapper = new QSignalMapper(this);
    connect(windowMapper,SIGNAL(mapped(QWidget*)),this,
            SLOT(setActiveSubwindow(QWidget *)));

    createActions(); // 创建菜单、工具栏、状态栏等相关操作操作（动作集合）
    createMenus(); // 创建菜单栏
    createToolBars(); // 创建工具条
    initStatusBar(); // 初始化MainWindow 自带的状态条对象
    updateMenus();

    resize(900,600);

}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *e)
{
    mdiArea->closeAllSubWindows();
    if(mdiArea->currentSubWindow())
    {
        e->ignore();
    }else{
        e->accept();
    }
}
//void MainWindow::mouseMoveEvent(QMouseEvent *event)
//{
//    updateMenus();
//    QMainWindow::mouseMoveEvent(event);
//}
//void MainWindow::mousePressEvent(QMouseEvent *event)
//{
//    updateMenus();
//    QMainWindow::mousePressEvent(event);
//}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    updateMenus();
    QMainWindow::mouseReleaseEvent(event);
}
//void MainWindow::keyPressEvent(QKeyEvent *event)
//{
//    updateMenus();
//    QMainWindow::keyPressEvent(event);
//}
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    updateMenus();
    QMainWindow::keyPressEvent(event);
}

MyTextEdit *MainWindow::createMyTextEdit()
{
    MyTextEdit *te = new MyTextEdit;
    return  te;

}
void MainWindow::setActiveSubwindow(QWidget *window)
{
    if(!window)
        return ;
    mdiArea->setActiveSubWindow((QMdiSubWindow*)window);
    updateStyleMenusStatus();
}

void MainWindow::initStatusBar()
{
    // MainWindow自带的一个对象
    statusBar()->showMessage(tr("准备就绪."));
}

void MainWindow::enabledText() // 使得【格式】下的各个子菜单项可用
{
//    MyTextEdit* pte=getActiveMyTextEdit();

//    boldAct->setEnabled(pte?true:false);
//    italicAct->setEnabled(pte?true:false);
//    underlineAct->setEnabled(pte?true:false);
//    leftAlignAct->setEnabled(pte?true:false);
//    centerAlignAct->setEnabled(pte?true:false);
//    rightAlignAct->setEnabled(pte?true:false);
//    justifyAlignAct->setEnabled(pte?true:false);
//    colorAct->setEnabled(pte?true:false);
}

MyTextEdit *MainWindow::getActiveMyTextEdit() // 获取已经得到焦点 编辑框
{
    if(mdiArea->activeSubWindow())
        return (MyTextEdit*)mdiArea->activeSubWindow()->widget();
    return nullptr;
}

QMdiSubWindow *MainWindow::findMyTextEdit(const QString&filename)
{
    QString filepath = QFileInfo(filename).canonicalFilePath();
    for(auto i:mdiArea->subWindowList())
    {
        if(((MyTextEdit*)i->widget())->getCurrentFile()==filepath)
            return i;
    }
    return nullptr;
}



void MainWindow::undo()
/*原生QTextEdit 支持undo、redo操作，
 * 并且会自动捕获 对应快捷键 ctrl+z、ctrl+y事件，
 * 不会将其发送给父组件，使得MainWindows窗口的undo、redo没有效果。
 *重写QTextEdit 的event函数，过滤 ctrl+z、ctrl+y事件，
 * 发送给父组件，使得父组件 可以处理该事件
 * */
{
    MyTextEdit *pte = getActiveMyTextEdit();
    if(pte)
    {
        pte->undo();
        statusBar()->showMessage(pte->getCurrentFileName()+" 撤销操作",
                                 status_bar_time1);
    }
}
void MainWindow::redo()
{
    MyTextEdit *pte = getActiveMyTextEdit();
    if(pte)
    {
        pte->redo(); // 恢复
        statusBar()->showMessage(pte->getCurrentFileName()+" 恢复操作",
                                 status_bar_time1);
    }
}
void MainWindow::cut()
{
    MyTextEdit *pte = getActiveMyTextEdit();
    if(pte) pte->cut();
}
void MainWindow::copy()
{
    MyTextEdit *pte = getActiveMyTextEdit();
    if(pte) pte->copy();
}
void MainWindow::paste()
{
    MyTextEdit *pte = getActiveMyTextEdit();
    if(pte) pte->paste();
}


void MainWindow::about()
{
    QMessageBox::about(this,tr("关于 富文本编辑器v0.1"),tr("此软件是基于Qt5实现的文字处理软件"));
}
void MainWindow::aboutQt()
{
    QApplication::aboutQt();
}






