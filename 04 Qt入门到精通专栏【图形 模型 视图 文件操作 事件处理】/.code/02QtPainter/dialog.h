#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include "paintarea.h"


class Dialog : public QWidget
{
    Q_OBJECT

    PaintArea *ppaintArea;
    QLabel *plabel;
    QComboBox *pComboBox;
    QGridLayout *pgridLay;
    QHBoxLayout *pHBoxLay;

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void selectDrawShape(int);
};
#endif // DIALOG_H
