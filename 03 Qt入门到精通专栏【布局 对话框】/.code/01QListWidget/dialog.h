#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QListWidget>
#include <QStackedWidget>
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    QListWidget *pListWidget;
    QStackedWidget *pStackWidget;
    QLabel *plabel1,*plabel2,*plabel3;
    QVBoxLayout *pVBoxLay;

    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
