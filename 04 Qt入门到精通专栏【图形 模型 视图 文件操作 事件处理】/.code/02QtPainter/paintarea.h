#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPainter>

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = nullptr);
    enum Shape{Line,Rectangle};

    void setShape(Shape);
    void setPen(QPen);
    void setBrush(QBrush);

    void paintEvent(QPaintEvent *event) override;
    void setfillrule(Qt::FillRule);

signals:

private:
    Shape shape;
    QPen pen;
    QBrush brush;
    Qt::FillRule fillrule;

};

#endif // PAINTAREA_H
