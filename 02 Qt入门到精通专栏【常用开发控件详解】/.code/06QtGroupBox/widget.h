#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QVBoxLayout>  // 组合框中布局方式，QVBoxLayout/QHBoxLayout
#include <QGridLayout>

class Widget : public QWidget
{
    Q_OBJECT
    QRadioButton *pRadioBtn1,*pRadioBtn2,*pRadioBtn3,*pRadioBtn4;
    QCheckBox *pCheckBtn1,*pCheckBtn2,*pCheckBtn3,*pCheckBtn4;
    QCheckBox *pCheckBtn5,*pCheckBtn6,*pCheckBtn7,*pCheckBtn8;
    QCheckBox *pCheckBtn9,*pCheckBtnA,*pCheckBtnB,*pCheckBtnC;

    QGroupBox *pGroupBox1,*pGroupBox2,*pGroupBox3,*pGroupBox4;
    QVBoxLayout *pVBoxLay1,*pVBoxLay2,*pVBoxLay3,*pVBoxLay4;
    QHBoxLayout *pHBoxLay1;

    QGridLayout *pGridLay;

private slots:
    void clickGroup2(int state);

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
