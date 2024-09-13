#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QPushButton>
#include <QGridLayout>
#include <QFrame>


class Dialog : public QDialog
{
    Q_OBJECT
    QPushButton *ppushBtn;
    QGridLayout *pgridLay;
    QFrame *pframe;

private slots:
    void clickColorBtn();
public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
};
#endif // DIALOG_H
