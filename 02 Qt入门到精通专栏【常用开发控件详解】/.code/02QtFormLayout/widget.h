#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QFormLayout *pFormLay;
    QLineEdit *pLedit1;
    QLineEdit *pLedit2;
    QLineEdit *pLedit3;
    QLineEdit *pLedit4;


};
#endif // WIDGET_H
