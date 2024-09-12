#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include <QTextBrowser>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    void TestLabel();
    void TestTextBrowser();
    void TestProcessBar();

private slots:
    void clickTestProcessBar();

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
