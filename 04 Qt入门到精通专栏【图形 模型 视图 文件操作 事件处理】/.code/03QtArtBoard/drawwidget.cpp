#include "drawwidget.h"

ArtBoard::ArtBoard(QWidget *parent) : QWidget(parent)
{
    setPalette(Qt::white);
    setAutoFillBackground(true);
    ppix = new QPixmap(size());
    ppix->fill(Qt::white);

    // 设置绘制区域
    setMinimumSize(600,400);

}

void ArtBoard::mouseMoveEvent(QMouseEvent *event)
{
    QPainter *painter = new QPainter();
    QPen pen;
    pen.setStyle((Qt::PenStyle)lineStyle);
    pen.setWidth(lineWidth);
    pen.setColor(lineColor);

    painter->begin(ppix);
    painter->setPen(pen);
    painter->drawLine(startPos,event->pos());
    painter->end();

    startPos = event->pos();
    update();
}
void ArtBoard::mousePressEvent(QMouseEvent *event)
{
    startPos=event->pos();
}
void ArtBoard::paintEvent(QPaintEvent *event)
{
    // 将绘制好的 像素信息 输入到控件中
    QPainter painter(this);
    painter.drawPixmap(QPoint(0,0),*ppix);
}

void ArtBoard::resizeEvent(QResizeEvent *event)
{
    if(height()>ppix->height()||width()>ppix->width())
    {
        QPixmap *newPix = new QPixmap(size());
        newPix->fill(Qt::white);
        QPainter painter(newPix);
        painter.drawPixmap(QPoint(0,0),*ppix);
        delete ppix;
        ppix = newPix;

    }
    QWidget::resizeEvent(event);
}

void ArtBoard::setLineStyle(int s)
{
    lineStyle = s;
}
void ArtBoard::setLineWidth(int w)
{
    lineWidth = w;
}
void ArtBoard::setLineColor(QColor c)
{
    lineColor = c;
}
void ArtBoard::clearArtboard()
{
    QPixmap *cPix = new QPixmap(size());
    cPix->fill(Qt::white);
    ppix=cPix;
    update();
}
