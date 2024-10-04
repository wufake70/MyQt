#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE


class Dialog : public QDialog
{
    Q_OBJECT
    QTextEdit *pte;

private slots:

    void getHostname();
    void getHostIpInfo();
    void on_pushButton_2_clicked();

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
