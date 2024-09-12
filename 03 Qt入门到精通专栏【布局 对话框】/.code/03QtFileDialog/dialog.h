#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QFileDialog>
#include <QFile>
#include <QToolTip>
#include <QMouseEvent>

/*
 * 继承 QLineEdit类，并重写mouseMoveEvent事件回调函数，
 * 以实现鼠标悬停效果
 * */
class MyQLineEdit: public QLineEdit
{
public:
    MyQLineEdit(QWidget *parent=nullptr):QLineEdit(parent){};
    MyQLineEdit(QString str,QWidget *parent=nullptr)
        :QLineEdit(parent)
    {
        this->setText(str);
    };
protected:
    void leaveEvent(QEvent *event) override;
    void mouseMoveEvent(QMouseEvent *e) override;

};

class Dialog : public QDialog
{
    Q_OBJECT
    QLabel *plabel1;
    QLabel *plabel2;
    MyQLineEdit *plineEdit1;
    MyQLineEdit *plineEdit2;
    QPushButton *ppushBtn;
    QGridLayout *pgridLay;
    QFile *pfile;


private slots:
    void clickSelectFileBtn();

public:
    Dialog(QWidget *parent = nullptr);
    virtual ~Dialog();
};
#endif // DIALOG_H
