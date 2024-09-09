#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListView>
#include <QStringList>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    QListView *pListView;
    QStringList *pStringList;
    QStringListModel *pStringListModel;

    void resizeEvent(QResizeEvent *event);
private slots:
    void clickListViewItem(const QModelIndex&);

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
