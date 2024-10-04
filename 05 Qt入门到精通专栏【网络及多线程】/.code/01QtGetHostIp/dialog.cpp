#include "dialog.h"
#include "ui_dialog.h"

QStringList InterfaceTypeName =  {
    "Unknown",
    "Loopback",
    "Virtual",
    "Ethernet",
    "Slip",
    "CanBus",
    "Ppp",
    "Fddi",
    "Wifi",
    "Ieee80211(Wifi)",
    "Phonet",
    "Ieee802154",
    "SixLoWPAN",
    "Ieee80216",
    "Ieee1394",

};

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    pte=nullptr;
    getHostname();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::getHostname()
{

    ui->lineEdit->setText(QHostInfo::localHostName());
    QHostInfo hostinfo = QHostInfo::fromName(QHostInfo::localHostName());
    QList<QHostAddress>	ip_list=hostinfo.addresses();
    QString temp;
    foreach(auto i,ip_list)
    {
        if(i.protocol()==QAbstractSocket::IPv4Protocol){
            temp=i.toString();
            break;
        }
    }
    ui->lineEdit_2->setText(temp);



}
void Dialog::getHostIpInfo()
{
    QString temp;
    QList<QNetworkInterface> net_list = QNetworkInterface::allInterfaces();
    foreach(auto i,net_list)
    {
        temp += "Dvice name : "+i.name()+"\n";
        temp += "Mac address: "+i.hardwareAddress()+"\n";
        temp += "Interface type: " + InterfaceTypeName[i.type()] + "\n";
        foreach(auto j,i.addressEntries()) // ipv4,ipv6
        {
            temp += "Ip address:" +j.ip().toString()+"\n";
            temp += "mask address:" +j.netmask().toString()+"\n";
            temp += "broadcast address:" +j.broadcast().toString()+"\n";
        }
        temp += "-----------------------------------------------\n";
    }
    if(pte==nullptr)
    {
        pte = new QTextEdit();
        pte->resize(600,400);
        pte->setFontPointSize(13);
        pte->setFontWeight(10);
    }
    pte->setText("");
    pte->setText(temp);
    pte->show();
}



void Dialog::on_pushButton_2_clicked()
{
    getHostIpInfo();
}
