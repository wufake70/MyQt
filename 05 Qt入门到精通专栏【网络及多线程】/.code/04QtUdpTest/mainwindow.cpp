#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    pUdpSocket = new QUdpSocket(this);
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    ui->comboBox->setEditable(true);
    ui->comboBox->addItems(getLocalHostIps());

    connect(pUdpSocket,SIGNAL(readyRead()),SLOT(SocketReadData()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QStringList MainWindow::getLocalHostIps()
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

void MainWindow::SocketReadData()
{
    // 读取接收到的数据报信息
    // 用此函数返回true至少有一个数据报需要读取
    while(pUdpSocket->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(pUdpSocket->pendingDatagramSize());
        QHostAddress address;
        quint16 port;
        // 通过readDatagram（）此函数读取数据报
        pUdpSocket->readDatagram(data.data(),data.size(),
                                 &address,&port);
        ui->textEdit->append("来自 "+address.toString()+":"+
                             QString::number(port));
        ui->textEdit->append("[in]"+data);
    }
}
void MainWindow::on_pushButton_clicked()
{
    // 本机端口
    quint16 port = ui->spinBox->value();

    if(pUdpSocket->bind(port))
    {
        ui->textEdit->append("本机"+QString::number(port)+
                             "端口绑定成功");
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
    }else{
        ui->textEdit->append("本机"+QString::number(port)+
                             "端口绑定失败");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    pUdpSocket->abort();
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->textEdit->append("解除绑定");
}

void MainWindow::on_pushButton_3_clicked()
{
    QString msg = ui->lineEdit->text();
    QByteArray data = msg.toUtf8();

    // 不建议发送大于 512 字节的数据报，因为即使成功发送，
    // 它们也可能会在到达最终目的地之前被 IP 层分割。
    pUdpSocket->writeDatagram(data,
                              QHostAddress(ui->comboBox->currentText()),
                              ui->spinBox_2->value());
    ui->textEdit->append("[out]"+msg);
    ui->lineEdit->setFocus();
}

void MainWindow::on_pushButton_4_clicked()
{
    QString msg = ui->lineEdit->text();
    QByteArray data = msg.toUtf8();

    // 不建议发送大于 512 字节的数据报，因为即使成功发送，
    // 它们也可能会在到达最终目的地之前被 IP 层分割。
    // 广播 主机号为255，端口必须相同
    QHostAddress address(QHostAddress::Broadcast);
    pUdpSocket->writeDatagram(data,
                              QHostAddress(ui->comboBox->currentText().replace(QRegExp(".\\d+$"),".255")),
                              ui->spinBox_2->value());
    ui->textEdit->append("[out]"+msg);
    ui->lineEdit->setFocus();
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->textEdit->setText("");
}
