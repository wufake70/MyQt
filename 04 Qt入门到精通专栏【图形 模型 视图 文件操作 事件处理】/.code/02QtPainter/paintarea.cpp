#include "paintarea.h"

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
    // 调色板
    setPalette(QPalette(Qt::blue));
    setAutoFillBackground(true);


}

void PaintArea::setShape(Shape obj)
{
    shape = obj;
    update();
}
//void PaintArea::setPen(QPen obj)
//{
//    pen = obj;
//    update();
//}
//void PaintArea::setBrush(QBrush obj)
//{
//    brush = obj;
//    update();
//}

void PaintArea::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(pen);
    p.setBrush(brush);

    QRect rect1(55,110,290,180);

    switch (shape) {
    case Line:
        p.drawLine(rect1.topLeft(),
                   rect1.bottomRight());
        break;
    case Rectangle:
        p.drawRect(rect1);
        break;

    }

}
void PaintArea::setfillrule(Qt::FillRule rule)
{
    fillrule = rule;
    update();
}
