#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QGridLayout>

class Dialog : public QDialog
{
    Q_OBJECT
    QGridLayout *pgridLay;
    QLabel *plabel;
    QPushButton *ppushuBtn;

private slots:
    void testCustomMsg();

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
};
#endif // DIALOG_H
