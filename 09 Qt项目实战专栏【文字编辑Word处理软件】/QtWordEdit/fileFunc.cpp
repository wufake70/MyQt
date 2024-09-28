#include "mainwindow.h"


void MainWindow::fileNew()
{
    MyTextEdit *pte=createMyTextEdit();
//    pte->setParent(this); // pte默认将MainWindow作为父组件
    mdiArea->addSubWindow(pte); // 将新创建文档编辑窗口 加入MDI容器进行管理
    pte->newFile();
    pte->show();
    pte->showMaximized();
    textInitStyle();
//    enabledText();
}
void MainWindow::fileOpen()
{
    QString file_name = QFileDialog::getOpenFileName(this,tr("打开"),
                                                    nullptr,tr("html文档(*.html *.htm)"));
    if(!file_name.isEmpty())
    {
        // 是否已经存在
        QMdiSubWindow *exist_te=findMyTextEdit(file_name);
        if(exist_te)
        {
            mdiArea->setActiveSubWindow(exist_te);
            statusBar()->showMessage(file_name+" 已存在",status_bar_time1);
            return ;
        }

        MyTextEdit *pte = new MyTextEdit;
        if(pte->loadFile(file_name))
        {
            mdiArea->addSubWindow(pte);
            pte->show();
            statusBar()->showMessage(file_name+" 已加载",status_bar_time1);
            pte->showMaximized();
            textInitStyle();
//            enabledText();
        }else{
            pte->close();
        }
    }
}
void MainWindow::fileSave()
{
    MyTextEdit *pte = getActiveMyTextEdit();
    if(pte&&pte->save())
        statusBar()->showMessage(pte->getCurrentFileName()+" 已保存",
                                 status_bar_time1);
    mdiArea->setActiveSubWindow((QMdiSubWindow *)pte);

}

void MainWindow::fileSaveAs()
{
    MyTextEdit *pte = getActiveMyTextEdit();
    if(pte&&pte->saveAs())
        statusBar()->showMessage(pte->getCurrentFileName()+" 已保存",
                                 status_bar_time1);
    mdiArea->setActiveSubWindow((QMdiSubWindow *)pte);
}

void MainWindow::filePrint()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *pdlg=new QPrintDialog(&printer,this);
    MyTextEdit* pte =  getActiveMyTextEdit();
    if(pte->textCursor().hasSelection())
    pdlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    pdlg->setWhatsThis(tr("打印文档"));
    if(pdlg->exec()==QDialog::Accepted)
        pte->print(&printer);
    delete pdlg;
}
void MainWindow::filePrintPreview()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer,this);
    connect(&preview,SIGNAL(paintRequested(QPrinter*)),SLOT(printPreview(QPrinter*)));
    preview.exec();
}
void MainWindow::printPreview(QPrinter* painter)
{
    getActiveMyTextEdit()->print(painter);
}
