#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSlider>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QToolTip>
#include <QMouseEvent>
#include "pixelitem.h"

class MyQSlider: public QSlider
{
public:
    MyQSlider(Qt::Orientation orientation,QWidget *parent = nullptr){
        setOrientation(orientation);
    };
    QPoint mousePos;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;

};


class Widget : public QWidget
{
    Q_OBJECT

    QFrame* pControlFreme;
    QHBoxLayout *pHBoxLay;
    QVBoxLayout *pVBoxLay;

    QGroupBox *pGroupBox1;
    QGroupBox *pGroupBox2;
    QGroupBox *pGroupBox3;

    QVBoxLayout *pGroupBox1VBoxLay;
    QVBoxLayout *pGroupBox2VBoxLay;
    QVBoxLayout *pGroupBox3VBoxLay;

    MyQSlider *pSlider1;
    MyQSlider *pSlider2;
    MyQSlider *pSlider3;

    QPixmap *pImg;

    QGraphicsScene *pSence;
    PixelItem *pItem;
    QGraphicsView *pView;


private slots:
    void RotateImg(int);
    void ScaleImg(int);
    void TiltImg(int);

    void InitControlFrame();

protected:

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
