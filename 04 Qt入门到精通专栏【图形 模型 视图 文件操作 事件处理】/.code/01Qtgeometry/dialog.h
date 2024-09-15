#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>
//#include <QWidget>

class Dialog : public QDialog
{
    Q_OBJECT

    QLabel *plabel0;
    QLabel *plabel1;
    QLabel *plabel2;
    QLabel *plabel3;
    QLabel *plabel4;
    QLabel *plabel5;
    QLabel *plabel6;
    QLabel *plabel7;
    QLabel *plabel8;
    QLabel *plabel9;
    QLabel *plabel10;
    QLabel *plabel11;

    QGridLayout *pgridLay;

    void updata();

protected:

    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;



public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
};
#endif // DIALOG_H
