#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QApplication>


class Widget : public QWidget
{
    Q_OBJECT
    QTabWidget *pTabWidget;
    QWidget *pSubWidget1,*pSubWidget2,*pSubWidget3;
protected:
    void resizeEvent(QResizeEvent *event) override;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
