#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItems(GetLocalHostIps());
    pTcpSocket = new QTcpSocket(this);
    ui->pushButton_2->setEnabled(false);

    setCentralWidget(ui->widget);

    ui->textEdit->setReadOnly(true);
    ui->comboBox->setEditable(true);

    connect(pTcpSocket,SIGNAL(connected()),this,SLOT(connectServer()));
    connect(pTcpSocket,SIGNAL(disconnected()),this,SLOT(disconnectServer()));
    connect(pTcpSocket,SIGNAL(readyRead()),this,SLOT(readSocketData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::connectServer()
{
    ui->textEdit->append("已连接到服务器");
    ui->textEdit->append("服务器地址: "+
                         pTcpSocket->peerAddress().toString()+":"+
                         QString::number(pTcpSocket->peerPort()));
    ui->pushButton_2->setEnabled(true);
    ui->pushButton->setEnabled(false);
}
void MainWindow::disconnectServer()
{
    ui->textEdit->append("断开服务器连接");
    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(true);
}
void MainWindow::readSocketData()
{

    ui->textEdit->append("[in]"+pTcpSocket->readLine());
    // QTcpSocket::canReadLine 是以\n作为一行的标志，返回真假
//    while (pTcpSocket->canReadLine()) {
//        QString temp = ui->textEdit->toPlainText();
//        temp+="[in]"+pTcpSocket->readLine();
//        ui->textEdit->setPlainText(temp);
//    }
}
void MainWindow::on_pushButton_clicked()
{
    QString ip = ui->comboBox->currentText();
    unsigned short port = ui->spinBox->value();
    QHostAddress address(ip);
    pTcpSocket->connectToHost(address,port);
}

void MainWindow::on_pushButton_2_clicked()
{
    if(pTcpSocket->state()==QAbstractSocket::ConnectedState)
    {
        pTcpSocket->disconnectFromHost();

    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(pTcpSocket->state()==QAbstractSocket::ConnectedState&&
            !ui->lineEdit_2->text().isEmpty())
    {
        QString msg = ui->lineEdit_2->text();
        ui->textEdit->append("[out]"+msg);
//        msg+="\n";
        QByteArray data = msg.toUtf8();
        pTcpSocket->write(data);
        ui->lineEdit_2->clear();
    }
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(pTcpSocket->state()==QAbstractSocket::ConnectedState)
    {
        pTcpSocket->disconnectFromHost();

    }
    event->accept();
}

QStringList MainWindow::GetLocalHostIps()
{

    QHostInfo hostinfo = QHostInfo::fromName(QHostInfo::localHostName());
    QStringList result;
    QList<QHostAddress> hostlist = hostinfo.addresses();
    if(!hostlist.isEmpty())
    {
        foreach(auto host_addr,hostlist)
        {
            if(host_addr.protocol()==QAbstractSocket::IPv4Protocol)
            {
                result << host_addr.toString();
            }
        }
    }

    return result;

}
