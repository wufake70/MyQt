#include "textedit.h"
#include <QFile>
#include <QTextCodec>
#include <QFileDialog>
#include <QTextDocumentWriter>
#include <QFileInfo>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTextCursor>
#include <QTextListFormat>
#include <QTextList>
#include <QCoreApplication>
#include <QMainWindow>


TextEdit::TextEdit()
{
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = false;
}

void  TextEdit::newFile()
{
    static int sequenceNumber=1;
    isUntitled = true;
    curFile = tr("Untitled-%1").arg(sequenceNumber++);
    setWindowTitle("[*]"+curFile);
    connect(document(),SIGNAL(contentsChanged()),this,
            SLOT(documentIsModified()));
}
bool  TextEdit::loadFile(const QString &fileName)
{
    if(!fileName.isEmpty())
    {
        if(!QFile::exists(fileName))
        {
            return false;
        }
        QFile file(fileName);
        file.open( QIODevice::ReadOnly|
                   QIODevice::WriteOnly); // ***打开模式
        QByteArray data=file.readAll();
        QTextCodec *codec=Qt::codecForHtml(data);
        QString str=codec->toUnicode(data);

        if(Qt::mightBeRichText(str))
        {
            this->setHtml(str);
        }else {

            str=QString::fromLocal8Bit(data);
            this->setPlainText(str);
        }
        setCurrentFile(fileName);
        connect(document(),SIGNAL(contentsChanged()),this,
                SLOT(documentIsModified())); // 文档发生改变，将该编辑窗口设置成已修改未保存状态
        return true;
    }
    return false;
}

bool  TextEdit::save()
{
    if(isUntitled)
    {
        return saveAs(); // 未命名文件
    }else{
        return saveFile(curFile);
    }
}

bool  TextEdit::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("另存为"),
                                                    curFile,
                                                    tr("html文档(*.html *.htm)"
                                                       ";;所有文件(*.*)"));
    if(fileName.isEmpty())
    {
        return false;
    }else{
        return saveFile(fileName);
    }
}
bool  TextEdit::saveFile(QString fileName)
{
    if(!fileName.endsWith(".html",Qt::CaseInsensitive)&&
            !fileName.endsWith(".htm",Qt::CaseInsensitive))
    {
        fileName+=".html";
    }

    QTextDocumentWriter writer(fileName);
    bool write_status = writer.write(this->document());
    if(write_status)
    {
        setCurrentFile(fileName);
    }
    return write_status;
}
QString  TextEdit::getCurrentFileName()
{
    return isLocalFile(curFile);

}
void TextEdit::setCurrentFile(const QString &fileName)
{
    curFile=QFileInfo(fileName).canonicalFilePath();
    isUntitled = false;
    document()->setModified(false);
    setWindowModified(false);
    // [*]通常用作修改标记，用于指示文件的修改状态
    setWindowTitle("[*]"+getCurrentFileName());
}

// 格式设置
void  TextEdit::mergeFormationOnWordOrSelection(const QTextCharFormat&format)
{
    QTextCursor cursor = this->textCursor();
    if(!cursor.hasSelection())
    {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(format);
    this->mergeCurrentCharFormat(format);
}
void  TextEdit::setAlign(int align)
{

    switch (align) {
    case 1:
        this->setAlignment(Qt::AlignLeft|Qt::AlignAbsolute);
        break;

    case 2:
        this->setAlignment(Qt::AlignCenter|Qt::AlignAbsolute);
        break;

    case 3:
        this->setAlignment(Qt::AlignRight|Qt::AlignAbsolute);
        break;

    case 4:
        this->setAlignment(Qt::AlignJustify); //horizontal 两端对齐
        break;

    }

}
void  TextEdit::setListStyle(int style)
{
    //
    QTextCursor cursor = this->textCursor();
    QTextListFormat::Style stylename = QTextListFormat::ListStyleUndefined;
    QTextFormat tfmt;
    switch (style) {
    case 1:
        stylename = QTextListFormat::ListDisc;
        break;
    case 2:
        stylename = QTextListFormat::ListCircle;
        break;
    case 3:
        stylename = QTextListFormat::ListSquare;
        break;
    case 4:
        stylename = QTextListFormat::ListDecimal;
        break;
    case 5:
        stylename = QTextListFormat::ListLowerAlpha;
        break;
    case 6:
        stylename = QTextListFormat::ListUpperAlpha;
        break;
    case 7:
        stylename = QTextListFormat::ListLowerRoman;
        break;
    case 8:
        stylename = QTextListFormat::ListUpperRoman;
        break;
    }

    cursor.beginEditBlock(); //指示文档上一组编辑操作的开始
    QTextBlockFormat blockFmt = cursor.blockFormat();// 光标所在的块的格式
    QTextListFormat listFmt;

    if (cursor.currentList()) { // 当前光标是否存在列表样式
        listFmt = cursor.currentList()->format();
        if (style == 0) { // 无列表格式
            QString txt = cursor.selectedText();

            if(txt.isEmpty() || !txt.contains(0x2029)) // 0x2029换行符
            {   // 单行格式化
                cursor.select(QTextCursor::LineUnderCursor);
                txt = cursor.selectedText();
                cursor.movePosition(QTextCursor::EndOfLine);
                cursor.movePosition(QTextCursor::Left,
                                    QTextCursor::KeepAnchor,
                                    txt.length()+1);  // del <ul>、\t

                cursor.removeSelectedText();
                QKeyEvent backspace(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
                if(!txt.isEmpty()){
                    cursor.insertText("\n");
                    cursor.insertText(txt);
                }
            }else{
                int end = cursor.selectionEnd();
                int start = cursor.selectionStart();
                cursor.movePosition(QTextCursor::Start); // StartOfBlock、StartOfLine只能获取cursor起始位置所在行start位置
                cursor.movePosition(QTextCursor::Right,QTextCursor::MoveAnchor,start);
                cursor.movePosition(QTextCursor::StartOfLine);
                start = cursor.position();
                cursor.movePosition(QTextCursor::Start);
                cursor.movePosition(QTextCursor::Right,QTextCursor::MoveAnchor,end);
                cursor.movePosition(QTextCursor::EndOfLine);
                end = cursor.position();
                // 多行选中
                cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor,
                                    end-start+1);

                setTextCursor(cursor);
                txt = cursor.selectedText();
                cursor.removeSelectedText();
                cursor.insertHtml(txt);
                // 在次选中
                cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor,
                                    end-start);
                setTextCursor(cursor);
            }
            cursor.endEditBlock();
            return;
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
        }
    } else {
        listFmt.setIndent(blockFmt.indent() + 1);
    }

    blockFmt.setIndent(0); //设置块的缩进
    cursor.setBlockFormat(blockFmt);

    listFmt.setStyle(stylename);
    cursor.createList(listFmt); // 更新列表格式
    cursor.endEditBlock(); // 指示文档上一组编辑操作的结束，从撤消/重做的角度来看，该操作应该作为单个操作出现
}

void  TextEdit::documentIsModified()
{
    setWindowModified(document()->isModified());// 窗口标题将带有“*”（星号）。
}


void TextEdit::closeEvent(QCloseEvent *event)
{
    if(maybeSave())
    {
        event->accept();
    }else{
        event->ignore();
    }
}

// 特定事件的过滤器会优先于event函数 执行
void TextEdit::mouseMoveEvent(QMouseEvent *event)
{
    QTextEdit::mouseMoveEvent(event);
    // **清除事件对象的接受标志参数，
    event->ignore(); // 不想要的事件可以传播到父窗口小部件
//    QCoreApplication::sendEvent(parentWidget(),event); // 发送事件过于频繁
}
void TextEdit::mousePressEvent(QMouseEvent *event)
{
    QTextEdit::mousePressEvent(event);
    event->ignore();
//    QCoreApplication::sendEvent(parentWidget(),event);
}
void TextEdit::mouseReleaseEvent(QMouseEvent *event)
{
    QTextEdit::mousePressEvent(event);
    event->ignore();
    QCoreApplication::sendEvent(parentWidget(),event);
}
bool TextEdit::event(QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->matches(QKeySequence::Undo)||
           keyEvent->matches(QKeySequence::Redo) ||
           keyEvent->matches(QKeySequence::Cut) ||
           keyEvent->matches(QKeySequence::Copy) ||
           keyEvent->matches(QKeySequence::Paste))
        {
            // 将撤销操作的事件传递给父级组件，即主窗口
            // parentWidget()->event(event); 被保护
            event->ignore();
            QCoreApplication::sendEvent(parentWidget(),event);
            return true;
        }
//        event->ignore();
//        QCoreApplication::sendEvent(parentWidget(),event);
    }

    if (event->type() == QEvent::KeyRelease)
    {
        event->ignore();
        QCoreApplication::sendEvent(parentWidget(),event);
    }

    return QTextEdit::event(event);
}

bool TextEdit::maybeSave()
{
    if(!document()->isModified())
    {
        return true;
    }
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this,tr("Qt Word"),
                               tr("文件 '%1' 已被修改，是否保存").arg(getCurrentFileName()),
                               QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
    // Discard 丢弃
    if(ret==QMessageBox::Save)
    {
        return save();
    }else if(ret==QMessageBox::Cancel){
        return false;
    }
    return true;
}

QString TextEdit::isLocalFile(const QString &fullFileName)
{
    QFileInfo fileinfo = QFileInfo(fullFileName);
    if(fileinfo.isFile())
    {
        return QFileInfo(fullFileName).fileName(); // 本地文件路径名
    }else {
        return fullFileName;    // 新建文件名字
    }
}
