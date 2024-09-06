#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QGridLayout *pGridLay;
    QPushButton *pBtn1;
    QPushButton *pBtn2;
    QPushButton *pBtn3;
    QPushButton *pBtn4;

};
#endif // WIDGET_H
