#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QColor>
#include <QPixmap>
#include <QPainter>
#include <QPalette>

class ArtBoard : public QWidget
{
    Q_OBJECT

    QPixmap *ppix;
    QPoint startPos;
    QPoint endPos;
    int lineStyle,lineWidth;
    QColor lineColor;

public:
    explicit ArtBoard(QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;


signals:
public slots:
    void setLineStyle(int);
    void setLineWidth(int);
    void setLineColor(QColor);
    void clearArtboard();
};

#endif // DRAWWIDGET_H
