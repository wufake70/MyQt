#include "pixelitem.h"

PixelItem::PixelItem(QPixmap *parent)
{
    pixmap = *parent;
}

// 需要重新绘制的区域
QRectF PixelItem::boundingRect() const
{
    return QRectF(-pixmap.width()/2,pixmap.height()/2,
                  pixmap.width(),pixmap.height());
}

void PixelItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *parent)
{
    // 左上角开始绘制
    painter->drawPixmap(-pixmap.width()/2,
                        pixmap.height()/2,
                        pixmap);
}
