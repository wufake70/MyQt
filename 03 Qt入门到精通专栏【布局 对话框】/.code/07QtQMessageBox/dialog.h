#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QToolTip>
#include <QScreen>
#include <QApplication>

class Dialog : public QDialog
{
    Q_OBJECT
    QPushButton *pQuesMboxBtn;
    QPushButton *pInfoMboxBtn;
    QPushButton *pWarnMboxBtn;
    QPushButton *pErrorMboxBtn;
    QPushButton *pAboutMboxBtn;
    QPushButton *pAboutQtMboxBtn;

    QScreen *pScreen;

    QGridLayout *pGridLay;

private slots:
    void clickQuesBtn();
    void clickInfoBtn();
    void clickWarnBtn();
    void clickErrorBtn();
    void clickAboutBtn();
    void clickAboutQtBtn();

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
};
#endif // DIALOG_H
