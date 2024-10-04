#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->widget);
    pTcpSocket = nullptr;
    pTcpServer = new QTcpServer(this);
    ui->comboBox->addItems(GetLocalHostIps());
    ui->pushButton_2->setEnabled(false);

    ui->textEdit->setReadOnly(true);
    ui->comboBox->setEditable(true);
    // 每次有新的连接可用时都会发出此信号。
    connect(pTcpServer,SIGNAL(newConnection()),this,SLOT(newSocketConnection()));
//    connect(pTcpServer, &QTcpServer::newConnection, this, &MainWindow::newSocketConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
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
void MainWindow::connectClient()
{
    ui->textEdit->append("客户端socket连接");
    ui->textEdit->append("客户端地址: "+
                         pTcpSocket->peerAddress().toString()+":"+
                         QString::number(pTcpSocket->peerPort()));

}

void MainWindow::disconnectClient()
{
    ui->textEdit->append("客户端socket断开连接");
    pTcpSocket->deleteLater();
    pTcpSocket = nullptr;
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

// 处理 处理新的连接
void MainWindow::newSocketConnection()
{
    if(!pTcpSocket)
    {
        pTcpSocket = pTcpServer->nextPendingConnection();
        connect(pTcpSocket,SIGNAL(connected()),this,SLOT(connectClient()));
        connectClient();
        connect(pTcpSocket,SIGNAL(readyRead()),this,SLOT(readSocketData()));
        connect(pTcpSocket,SIGNAL(disconnected()),this,SLOT(disconnectClient()));
        connect(pTcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                this,SLOT(OnSocketStateChanged(QAbstractSocket::SocketState)));
    }else{
        // 拒绝多个客户端连接
        QTcpSocket *tempSocket = pTcpServer->nextPendingConnection();
        // 数据包异步发送
        tempSocket->write(tr("仅一个客户端连接").toUtf8());
        connect(tempSocket, &QTcpSocket::bytesWritten, [=](qint64 bytes){
            if (bytes != -1) {
                tempSocket->disconnectFromHost();
                tempSocket->deleteLater();
            }
        });
    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(pTcpServer->isListening()) pTcpServer->close();
    event->accept();
}



void MainWindow::on_pushButton_clicked()
{
    QString ip = ui->comboBox->currentText();
    unsigned short port = ui->spinBox->value();
    QHostAddress address(ip);
    // 监听本机ip的目标端口
    pTcpServer->listen(address,port);
    ui->textEdit->append("开始监听");
    ui->textEdit->append("服务器地址: "+
                         address.toString()+":"+
                         QString::number(port));
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);

}

void MainWindow::on_pushButton_2_clicked()
{
    if(pTcpServer->isListening())
    {
        pTcpServer->close(); // 关闭端口监听
        if(pTcpSocket!=nullptr)
        {
            pTcpSocket->close();
            pTcpSocket->deleteLater();
            pTcpSocket = nullptr;
        }

        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(pTcpSocket!=nullptr&&
            pTcpSocket->state()==QAbstractSocket::ConnectedState&&
            !ui->lineEdit_2->text().isEmpty())
    {
        QString msg = ui->lineEdit_2->text();
        ui->textEdit->append("[out]"+msg);
//        msg+="\n"; // QTcpSocket::canReadLine 是以\n作为一行的标志，返回真假
        QByteArray data = msg.toUtf8();
        pTcpSocket->write(data);
        ui->lineEdit_2->clear();
    }
}
