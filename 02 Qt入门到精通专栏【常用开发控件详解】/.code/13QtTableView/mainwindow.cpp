#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVariant>
#include <QVector>
//#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitTableView();

}
void MainWindow::InitTableView()
{
    pStandardItemModel = new QStandardItemModel();
    // 表头
    pStandardItemModel->setHorizontalHeaderItem(0,new QStandardItem("id"));
    pStandardItemModel->setHorizontalHeaderItem(1,new QStandardItem("gender"));
    pStandardItemModel->setHorizontalHeaderItem(2,new QStandardItem("name"));
    pStandardItemModel->setHorizontalHeaderItem(3,new QStandardItem("score"));

    ui->tableView->setModel(pStandardItemModel);
    ui->tableView->setColumnWidth(0,50); // 设置列宽
    // 设置不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 数据
    QVector<QVector<QVariant>> *pvector = new QVector<QVector<QVariant>>(
                            {    {"1","Male","John",85,},
                               {"2","Female","Alice",92,},
                               {"3","Male","Michael",78,},
                               {"4","Female","Emily",95,},
                               {"5","Male","William",88,},
                               {"6","Female","Sophia",91,},
                               {"7","Male","James",82,},
                               {"8","Female","Olivia",96,},
                               {"9","Male","Benjamin",89,},
                               {"10","Female","Emma",94,},
                               {"11","Male","Matthew",83,},
                               {"12","Female","Isabella",97,},
                               {"13","Male","David",86,},
                               {"14","Female","Ava",93,},
                               {"15","Male","Joseph",80,},
                               {"16","Female","Mia",98,},
                               {"17","Male","Daniel",87,},
                               {"18","Female","Charlotte",99,},
                               {"19","Male","Andrew",84,},
                               {"20","Female","Grace",90,},
                           });

    int y = 0,x=0;;
    QStandardItem *pitem = nullptr;
    for(auto i:pvector[0])
    {
        x=0;
        for(auto j:i)
        {
            pitem = new QStandardItem(j.toString());
            pitem->setTextAlignment(Qt::AlignCenter);
            pStandardItemModel->setItem(y,x,pitem);
            x++;
        }
        y++;
    }
    // 排序
//    pStandardItemModel->sort(3,Qt::DescendingOrder);
    setWindowTitle("双击表头排序");
    connect(ui->tableView->horizontalHeader(),SIGNAL(sectionDoubleClicked(int)),this,SLOT(clickSort(int)));
    // 后四位每一位表示 每一行的排序状态
    headerSortFlag = 0;
}

void MainWindow::clickSort(int index)
{
    uchar mask[4];
    *(ulong*)&mask = 0x08040201;

    if((headerSortFlag&mask[index]) == mask[index]){

        pStandardItemModel->sort(index,Qt::AscendingOrder);
        headerSortFlag &= ~mask[index];
    }else{
        pStandardItemModel->sort(index,Qt::DescendingOrder);
        headerSortFlag |= mask[index];
    }
    headerSortFlag &= 0x0f;
}

MainWindow::~MainWindow()
{
    delete ui;
}

