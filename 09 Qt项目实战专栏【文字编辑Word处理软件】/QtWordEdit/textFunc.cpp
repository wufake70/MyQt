#include "mainwindow.h"

void MainWindow::textInitStyle()
{
    boldAct->setChecked(false);
    textBold();
    italicAct->setChecked(false);
    textItalic();
    underlineAct->setChecked(false);
    textUnderline();
    leftAlignAct->setChecked(true);
    textAlign(leftAlignAct);

    comboListStyle->setCurrentIndex(0);
//    textListStyle(comboListStyle->currentIndex());
    comboFont->setCurrentFont(QFont("宋体"));
    textFamily(comboFont->currentFont().toString());
    comboSize->setCurrentIndex(6);
    textSize(comboSize->currentText());
}

void MainWindow::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(boldAct->isChecked()?QFont::Bold:QFont::Normal);
    MyTextEdit *pte = getActiveMyTextEdit();
    if(pte) pte->mergeFormationOnWordOrSelection(fmt);
}

void MainWindow::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(italicAct->isChecked());
    MyTextEdit *pte = getActiveMyTextEdit();
    if(pte) pte->mergeFormationOnWordOrSelection(fmt);
}
void MainWindow::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(underlineAct->isChecked());
    MyTextEdit *pte = getActiveMyTextEdit();
    if(pte) pte->mergeFormationOnWordOrSelection(fmt);
}
void MainWindow::textAlign(QAction *a)
{
    MyTextEdit *pte = getActiveMyTextEdit();
    if(!pte) return;
    if(a==leftAlignAct){
        pte->setAlign(1);
    }else if(a==centerAlignAct){
        pte->setAlign(2);
    }else if(a==rightAlignAct){
        pte->setAlign(3);
    }else if(a==justifyAlignAct){
        pte->setAlign(4);
    }
}
void MainWindow::textListStyle(int styleIndex)
{
    MyTextEdit *pte = getActiveMyTextEdit();
    if(pte)
        pte->setListStyle(styleIndex);
}
void MainWindow::textFamily(const QString&f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    MyTextEdit *pte = getActiveMyTextEdit();
    if(pte)
        pte->mergeFormationOnWordOrSelection(fmt);
}
void MainWindow::textSize(const QString &p)
{
    short fsize = p.split(' ')[1].toShort();
    if(fsize>0){
        QTextCharFormat fmt;
        fmt.setFontPointSize(fsize);
        MyTextEdit *pte = getActiveMyTextEdit();
        if(pte)
            pte->mergeFormationOnWordOrSelection(fmt);
    }
}
void MainWindow::textColor()
{
    MyTextEdit *pte = getActiveMyTextEdit();
    QColor color = QColorDialog::getColor(pte->textColor(),this);
    if(!color.isValid()) return;
    QTextCharFormat fmt;
    fmt.setForeground(color);
    if(pte) pte->mergeFormationOnWordOrSelection(fmt);
    colorChanged(color); // 更新图标
}

void MainWindow::fontChanged(const QFont&f)
{
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText("字号: "+QString::number(f.pointSize())));
    boldAct->setChecked(f.bold());
    italicAct->setChecked(f.italic());
    underlineAct->setChecked(f.underline());
}
void MainWindow::colorChanged(const QColor&c)
{
    QPixmap pix(16,16);
    pix.fill(c);
    colorAct->setIcon(pix);
}
void MainWindow::alignmentChanged(Qt::Alignment a)
{
    if(a&Qt::AlignLeft){
        leftAlignAct->setChecked(true);
    }else if(a&Qt::AlignCenter){
        centerAlignAct->setChecked(true);
    }else if(a&Qt::AlignRight){
        rightAlignAct->setChecked(true);
    }else if(a&Qt::AlignJustify){
        justifyAlignAct->setChecked(true);
    }
}
