#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFontDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QEvent>
#include <QtDebug>

class MyLineEdit: public QLineEdit
{

public:
    MyLineEdit(QWidget *parent=nullptr):QLineEdit(parent) {};
    MyLineEdit(char *str,QWidget *parent=nullptr):QLineEdit(parent)
    {
        this->setText(str);
    };
protected:
//    void changeEvent(QEvent *) override;
};


class Dialog : public QDialog
{
    Q_OBJECT
    QPushButton *ppushBtn;
    QGridLayout *pgridLay;
    QLineEdit *plineEdit;

private slots:
    void clickColorBtn();
public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
};
#endif // DIALOG_H
