#include "widget.h"
#include "ui_widget.h"
#include <QScreen>
#include <QApplication>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("清单视图");
    QScreen *qScreen = QApplication::primaryScreen();
    resize(qScreen->size().width()*0.5,
           qScreen->size().height()*0.5);

    pListView = new QListView(this);
    pListView->setGeometry(width()*0.1/2,
                           height()*0.1/2,
                           width()*0.9,
                           height()*0.9);
    pStringList = new QStringList({"【2020】奇安信秋招Golang方向试卷3",
                             "【2020】奇安信秋招C/C++方向试卷3",
                             "【2020】奇安信秋招Java方向试卷3",
                             "【2020】奇安信秋招Java方向试卷2",
                             "【2020】奇安信秋招Java方向试卷1",
                             "【2020】奇安信秋招Golang方向试卷2",
                             "【2020】奇安信秋招Golang方向试卷1",
                             "【2020】奇安信秋招C/C++方向试卷2",
                             "【2020】奇安信秋招C/C++方向试卷1",
                             "【2020】奇安信秋招技术支持工程师试卷4",
                             "【2020】奇安信秋招技术支持工程师试卷3",
                             "【2020】奇安信秋招技术支持工程师试卷2",
                             "【2020】奇安信秋招技术支持工程师试卷1",
                             "【2020】奇安信秋招测试方向试卷3",
                             "【2020】奇安信秋招测试方向试卷2",});

    pStringListModel = new QStringListModel(*pStringList);
    pListView->setModel(pStringListModel);

    connect(pListView,SIGNAL(clicked(const QModelIndex&)),SLOT(clickListViewItem(const QModelIndex&)));

}

void Widget::clickListViewItem(const QModelIndex &index)
{
    QMessageBox::information(0,"fuckyou",index.data().toString(),0);
}


Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *event)
{
    pListView->setGeometry(width()*0.1/2,
                           height()*0.1/2,
                           width()*0.9,
                           height()*0.9);
}

