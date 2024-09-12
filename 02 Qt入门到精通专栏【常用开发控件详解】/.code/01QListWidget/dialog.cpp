#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    pVBoxLay = new QVBoxLayout(this);

    pListWidget = new QListWidget(this);
    for(int i=0;i<1000;i++)
    {
        pListWidget->addItem(QString("%1 %2").arg(QString::number(i),3,QLatin1Char('0')).arg(tr("tmd")));

    }

    pStackWidget = new QStackedWidget(this);
    plabel1 = new QLabel("tmd1");
    plabel2 = new QLabel("tmd2");
    plabel3 = new QLabel("tmd3");
    pStackWidget->addWidget(plabel1);
    pStackWidget->addWidget(plabel2);
    pStackWidget->addWidget(plabel3);

    pVBoxLay->addWidget(pListWidget);
    pVBoxLay->addWidget(pStackWidget);
    this->setLayout(pVBoxLay);

    // 默认显示第一个子控件
    pStackWidget->removeWidget(plabel1);


}

Dialog::~Dialog()
{
    delete ui;
}

