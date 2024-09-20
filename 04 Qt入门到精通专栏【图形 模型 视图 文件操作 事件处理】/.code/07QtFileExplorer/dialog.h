#ifndef DIALOG_H
#define DIALOG_H

#include <iostream>

#include <QDialog>
#include <QLineEdit>
#include <QDir>

#include <QListWidget>
#include <QListWidgetItem>

#include <QFileInfoList>
#include <QVBoxLayout>
#include <QStringList>

#include <QStack> // 先进的索引越小

class Dialog : public QDialog
{
    Q_OBJECT

    QLineEdit *pDirPathLineEdit;
    QListWidget *pListWidget;
    QVBoxLayout *pVBoxLay;
    QStack<QString> *pFullPath;

    void DisplayFileInfoList(QFileInfoList);
private slots:
    void ShowSubDir(QDir dir);
    void ShowDirItem(QListWidgetItem *item);


public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
};
#endif // DIALOG_H
