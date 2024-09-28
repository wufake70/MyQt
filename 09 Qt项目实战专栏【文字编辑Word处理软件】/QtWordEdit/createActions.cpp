#include "mainwindow.h"



void MainWindow::createActions()
{
    // 文件菜单动作
    newAct = new QAction(QIcon(icon_path+"filenew.png"),tr("new"),this);
    newAct->setShortcut(QKeySequence::New);
    newAct->setToolTip("新建文件"); //设置工具栏按钮的提示文本信息
    newAct->setStatusTip(tr("创建一个新的word文档."));  //设置状态栏提示文本信息
    connect(newAct,SIGNAL(triggered()),this,SLOT(fileNew()));

    openAct = new QAction(QIcon(icon_path+"fileopen.png"),tr("open"),this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setToolTip("打开文件");
    openAct->setStatusTip(tr("打开一个新的word文档."));
    connect(openAct,SIGNAL(triggered()),this,SLOT(fileOpen()));

    saveAct = new QAction(QIcon(icon_path+"filesave.png"),tr("save"),this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setToolTip("保存文件");
    saveAct->setStatusTip(tr("保存一个新的word文档."));
    connect(saveAct,SIGNAL(triggered()),this,SLOT(fileSave()));

    saveAsAct = new QAction(QIcon(icon_path+"filesave.png"),tr("save as"),this);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    saveAsAct->setToolTip("另存为");
    saveAsAct->setStatusTip(tr("另存为一个新的word文档."));
    connect(saveAsAct,SIGNAL(triggered()),this,SLOT(fileSaveAs()));

    printAct = new QAction(QIcon(icon_path+"fileprint.png"),tr("print"),this);
    printAct->setShortcut(QKeySequence::Print);
    printAct->setToolTip("打印");
    printAct->setStatusTip(tr("打印一个新的文档."));
    connect(printAct,SIGNAL(triggered()),this,SLOT(filePrint()));

    printPreviewAct = new QAction(tr("print preview"),this);
//    printPreviewAct->setShortcut(QKeySequence::Print);
    printPreviewAct->setToolTip("打印预览");
    printPreviewAct->setStatusTip(tr("预览打印效果."));
    connect(printPreviewAct,SIGNAL(triggered()),this,SLOT(filePrintPreview()));

    exitAct = new QAction(tr("exit"),this);
    exitAct->setToolTip("退出");
    exitAct->setStatusTip(tr("退出程序."));
    connect(exitAct,SIGNAL(triggered()),qApp,SLOT(closeAllWindows()));

    // 编辑菜单栏
    undoAct = new QAction(QIcon(icon_path+"editundo.png"),tr("undo"),this);
    undoAct->setShortcut(QKeySequence::Undo);
    undoAct->setToolTip("撤销");
    undoAct->setStatusTip(tr("撤销上一次操作."));
    connect(undoAct,SIGNAL(triggered()),this,SLOT(undo()));

    redoAct = new QAction(QIcon(icon_path+"editredo.png"),tr("redo"),this);
    redoAct->setShortcut(QKeySequence::Redo);
    redoAct->setToolTip("恢复");
    redoAct->setStatusTip(tr("恢复上一次操作."));
    connect(redoAct,SIGNAL(triggered()),this,SLOT(redo()));

    cutAct = new QAction(QIcon(icon_path+"editcut.png"),tr("cut"),this);
    cutAct->setShortcut(QKeySequence::Cut);
    cutAct->setToolTip("剪切");
    cutAct->setStatusTip(tr("选中的文本 进行剪切文字."));
    connect(cutAct,SIGNAL(triggered()),this,SLOT(cut()));

    copyAct = new QAction(QIcon(icon_path+"editcopy.png"),tr("copy"),this);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setToolTip("复制");
    copyAct->setStatusTip(tr("选中的文本 进行复制文字."));
    connect(copyAct,SIGNAL(triggered()),this,SLOT(copy()));

    pasteAct = new QAction(QIcon(icon_path+"editpaste.png"),tr("paste"),this);
    pasteAct->setShortcut(QKeySequence::Paste);
    pasteAct->setToolTip("粘贴");
    pasteAct->setStatusTip(tr("粘贴文字."));
    connect(pasteAct,SIGNAL(triggered()),this,SLOT(paste()));

    // 格式字体 菜单栏
    boldAct = new QAction(QIcon(icon_path+"textbold.png"),tr("bold"),this);
    boldAct->setCheckable(true); // **将动作设置为可选中状态
    boldAct->setShortcut(Qt::CTRL+Qt::Key_B);
    boldAct->setToolTip("加粗");
    boldAct->setStatusTip(tr("鼠标所在行/所选中的文本 进行加粗."));
    QFont bold;
    bold.setBold(true);
    boldAct->setFont(bold);
    connect(boldAct,SIGNAL(triggered()),this,SLOT(textBold()));

    italicAct = new QAction(QIcon(icon_path+"textitalic.png"),tr("italic"),this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(Qt::CTRL+Qt::Key_I);
    italicAct->setToolTip("倾斜");
    italicAct->setStatusTip(tr("鼠标所在行/所选中的文本 倾斜文字."));
    QFont italic;
    italic.setItalic(true);
    italicAct->setFont(italic);
    connect(italicAct,SIGNAL(triggered()),this,SLOT(textItalic()));

    underlineAct = new QAction(QIcon(icon_path+"textunderline.png"),tr("underline"),this);
    underlineAct->setCheckable(true);
    underlineAct->setShortcut(Qt::CTRL+Qt::Key_U);
    underlineAct->setToolTip("下划线");
    underlineAct->setStatusTip(tr("鼠标所在行/所选中的文本 添加下划线."));
    QFont underline;
    underline.setUnderline(true);
    underlineAct->setFont(underline);
    connect(underlineAct,SIGNAL(triggered()),this,SLOT(textUnderline()));

    // 段落格式组 菜单栏,align left、center、right、justify 四选一
    alignStyleGrp=new QActionGroup(this);
    connect(alignStyleGrp,SIGNAL(triggered(QAction*)),this,SLOT(textAlign(QAction*)));
    if(QApplication::isLeftToRight())
    {
        leftAlignAct=new QAction(QIcon(icon_path+"textleft.png"),tr("align left"),alignStyleGrp);
        centerAlignAct=new QAction(QIcon(icon_path+"textcenter.png"),tr("align center"),alignStyleGrp);
        rightAlignAct=new QAction(QIcon(icon_path+"textright.png"),tr("align right"),alignStyleGrp);
        justifyAlignAct = new QAction(QIcon(icon_path+"textjustify.png"),tr("align justify"),alignStyleGrp);
    }
    else{
        rightAlignAct=new QAction(QIcon(icon_path+"textright.png"),tr("align right"),alignStyleGrp);
        centerAlignAct=new QAction(QIcon(icon_path+"textcenter.png"),tr("align center"),alignStyleGrp);
        leftAlignAct=new QAction(QIcon(icon_path+"textleft.png"),tr("align left"),alignStyleGrp);
        justifyAlignAct = new QAction(QIcon(icon_path+"textjustify.png"),tr("align justify"),alignStyleGrp);
    }

    leftAlignAct->setShortcut(Qt::CTRL+Qt::Key_L);
    leftAlignAct->setCheckable(true);
    leftAlignAct->setToolTip("align left");
    leftAlignAct->setStatusTip(tr("鼠标所在行/所选中的文本 进行左对齐")); // 鼠标所在行/所选中的文本 进行

    centerAlignAct->setShortcut(Qt::CTRL+Qt::Key_E);
    centerAlignAct->setCheckable(true);
    centerAlignAct->setToolTip("align center");
    centerAlignAct->setStatusTip(tr("鼠标所在行/所选中的文本 进行居中"));

    rightAlignAct->setShortcut(Qt::CTRL+Qt::Key_R);
    rightAlignAct->setCheckable(true);
    rightAlignAct->setToolTip("align right");
    rightAlignAct->setStatusTip(tr("鼠标所在行/所选中的文本 进行右对齐"));

    justifyAlignAct->setShortcut(Qt::CTRL+Qt::Key_J);
    justifyAlignAct->setCheckable(true);
    justifyAlignAct->setToolTip("align justify");
    justifyAlignAct->setStatusTip(tr("鼠标所在行/所选中的文本 进行两端对齐"));

    QPixmap pix(16,16);
    pix.fill(Qt::black);
    colorAct = new QAction(pix,tr("color"),this);
    colorAct->setToolTip("颜色");
    colorAct->setStatusTip(tr("鼠标所在行/所选中的文本 设置颜色"));
    connect(colorAct,SIGNAL(triggered()),this,SLOT(textColor()));

    // 窗口管理菜单栏
    closeAct = new QAction(tr("close window"),this);
    closeAct->setStatusTip(tr("关闭当前窗口"));
    connect(closeAct,SIGNAL(triggered()),mdiArea,SLOT(closeActiveSubWindow()));

    closeAllAct = new QAction(tr("close all Subwindows"),this);
    closeAllAct->setStatusTip(tr("关闭所有子窗口"));
    connect(closeAllAct,SIGNAL(triggered()),mdiArea,SLOT(closeAllSubWindows()));

    tileWindowsAct = new QAction(tr("tile Subwindows"),this);
    tileWindowsAct->setStatusTip(tr("平铺子窗口"));
    connect(tileWindowsAct,SIGNAL(triggered()),mdiArea,SLOT(tileSubWindows()));

    cascadeWindowAct = new QAction(tr("cascade Subwindows"),this);
    cascadeWindowAct->setStatusTip(tr("堆叠子窗口"));
    connect(cascadeWindowAct,SIGNAL(triggered()),mdiArea,SLOT(cascadeSubWindows()));

    separateAct = new QAction(tr("separate"),this);
    separateAct->setStatusTip(tr("分离文档窗口"));
//    connect(separateAct,SIGNAL(triggered()),mdiArea,SLOT(closeAllSubWindows()));

    nextAct =new QAction(tr("next window"),this);
    nextAct->setShortcuts(QKeySequence::NextChild);
    nextAct->setStatusTip("移动焦点到下一个子窗口.");
    connect(nextAct,SIGNAL(triggered()),mdiArea,SLOT(activateNextSubWindow()));

    previousAct=new QAction(tr("previous window"),this);
    previousAct->setShortcuts(QKeySequence::PreviousChild);
    previousAct->setStatusTip("移动焦点到前一个子窗口.");
    connect(previousAct,SIGNAL(triggered()),mdiArea,SLOT(activatePreviousSubWindow()));

    // 帮助菜单
    aboutAct = new QAction(tr("about"),this);
    aboutAct->setStatusTip("关于该软件.");
    connect(aboutAct,SIGNAL(triggered()),this,SLOT(about()));

    aboutQtAct = new QAction(tr("about Qt"),this);
    aboutQtAct->setStatusTip("关于Qt.");
    connect(aboutQtAct,SIGNAL(triggered()),this,SLOT(aboutQt()));
}
