#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer> // 此类专门用于建立TCP连接并传输数据信息
#include <QtNetwork>  // 此模块提供开发TCP/IP客户端和服务器的类
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QTcpServer *pTcpServer; // tcp服务器
    QTcpSocket *pTcpSocket;
    QStringList GetLocalHostIps();


private slots:
    void connectClient();
    void disconnectClient();
    void readSocketData();
    void newSocketConnection();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

protected:
    void closeEvent(QCloseEvent *event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
