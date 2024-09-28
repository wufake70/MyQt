#include "mainwindow.h"


void MainWindow::updateMenus()//更新菜单 是否启用以及选中 的状态
{
    bool hasMyTextEdit=(getActiveMyTextEdit()!=nullptr); // 是否存在文档，用于判断启用相关操作
    undoAct->setEnabled(hasMyTextEdit);
    redoAct->setEnabled(hasMyTextEdit);
    saveAct->setEnabled(hasMyTextEdit);
    saveAsAct->setEnabled(hasMyTextEdit);
    printAct->setEnabled(hasMyTextEdit);
    printPreviewAct->setEnabled(hasMyTextEdit);
    pasteAct->setEnabled(hasMyTextEdit);
    boldAct->setEnabled(hasMyTextEdit);
    italicAct->setEnabled(hasMyTextEdit);
    underlineAct->setEnabled(hasMyTextEdit);
    leftAlignAct->setEnabled(hasMyTextEdit);
    centerAlignAct->setEnabled(hasMyTextEdit);
    rightAlignAct->setEnabled(hasMyTextEdit);
    justifyAlignAct->setEnabled(hasMyTextEdit);
    colorAct->setEnabled(hasMyTextEdit);

    // 窗口管理相关 QAction
    closeAct->setEnabled(true);
    closeAllAct->setEnabled(true);
    tileWindowsAct->setEnabled(true);
    cascadeWindowAct->setEnabled(true);
    separateAct->setEnabled(true);
    nextAct->setEnabled(true);
    previousAct->setEnabled(true);


    bool hasSelection = (getActiveMyTextEdit()&&
                         getActiveMyTextEdit()->textCursor().hasSelection());
    // 与文本选中相关的操作
    cutAct->setEnabled(hasSelection);
    copyAct->setEnabled(hasSelection);

    // 当前鼠标所在行或鼠标所选中的文本 样式菜单的选中状态
    updateStyleMenusStatus();
}

void MainWindow::updateWindowMenu()
{
    windowMenu->clear();
    windowMenu->addAction(closeAct);
    windowMenu->addAction(closeAllAct);
    windowMenu->addSeparator();
    windowMenu->addAction(tileWindowsAct);
    windowMenu->addAction(cascadeWindowAct);
    windowMenu->addAction(separateAct);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAct);
    windowMenu->addAction(previousAct);
    windowMenu->addSeparator();

    QList<QMdiSubWindow*> windows=mdiArea->subWindowList();
    separateAct->setVisible(!windows.isEmpty());

    QString text;
    for(int i=0;i<windows.size();i++)
    {
        MyTextEdit *pte=(MyTextEdit*)windows.at(i)->widget();
        text = tr("%1 %2").arg(i+1).arg(pte->getCurrentFileName());
        QAction *action = windowMenu->addAction(text);
        action->setCheckable(true);
        action->setChecked(pte==getActiveMyTextEdit());
        // 将动作关联到 组件
        windowMapper->setMapping(action, windows[i]);
        // 将action 的 triggered 信号映射到 windowMapper 的 map() 槽
        connect(action,SIGNAL(triggered()),windowMapper,SLOT(map()));
    }
//    enabledText();
}

void MainWindow::updateStyleMenusStatus()
{
    MyTextEdit *pte = getActiveMyTextEdit();
    if(!pte) return;
    QTextCharFormat tcfmt = pte->currentCharFormat();
    fontChanged(tcfmt.font());
    colorChanged(pte->textColor());
    alignmentChanged(pte->alignment());
}
