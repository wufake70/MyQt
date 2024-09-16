#ifndef PIXELITEM_H
#define PIXELITEM_H

#include <QGraphicsItem> // 抽象类，在派生类中实现 纯虚函数
#include <QPixmap>
#include <QPainter>

class PixelItem: public QGraphicsItem
{
    QPixmap pixmap;

public:
    PixelItem(QPixmap *parent=nullptr);

    // 刷新固定区域
    QRectF boundingRect() const;
    // 绘制操作
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *parent);

};

#endif // PIXELITEM_H
