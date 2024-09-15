#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initDrawWidget();
    initToolBar();

    setCentralWidget(pDrawWidget);
    resize(size());
}

void MainWindow::selectLineStyle(int i)
{
    pDrawWidget->setLineStyle(pcomboBoxLineStyle->itemData(i,Qt::UserRole).toInt());
}
void MainWindow::selectLineWidth(int i)
{
    pDrawWidget->setLineWidth(i);
}
void MainWindow::selectColor()
{
    QColor color = QColorDialog::getColor();
    if(color.isValid())
    {
        pDrawWidget->setLineColor(color);
        QPixmap pixmap(pbtnColor->sizeHint());
        pixmap.fill(color);
        pbtnColor->setIcon(QIcon(pixmap));
    }
}

void MainWindow::initDrawWidget()
{
    pDrawWidget = new ArtBoard(this);
    pDrawWidget->setLineColor(Qt::black);
    pDrawWidget->setLineStyle(Qt::SolidLine);
    pDrawWidget->setLineWidth(1);

}

void MainWindow::initToolBar()
{
    ptoolBar = new QToolBar(this);
    plabelLineStyle = new QLabel("LineStyle:",ptoolBar);
    pcomboBoxLineStyle = new QComboBox(ptoolBar);
    pcomboBoxLineStyle->addItem("实线",static_cast<int>(Qt::SolidLine));
    pcomboBoxLineStyle->addItem("虚线",static_cast<int>(Qt::DotLine));
    connect(pcomboBoxLineStyle,SIGNAL(activated(int)),this,SLOT(selectLineStyle(int)));

    plabelLineWidth = new QLabel("LineWidth:",ptoolBar);
    pspinBoxLineWidth = new QSpinBox(ptoolBar);
    pspinBoxLineWidth->setRange(1,72);
    connect(pspinBoxLineWidth,SIGNAL(valueChanged(int)),this,SLOT(selectLineWidth(int)));
    plabelLineWidth->setStyleSheet("margin-left:10px;");

    pbtnColor = new QToolButton(ptoolBar);
    QPixmap pixmap(pbtnColor->sizeHint());
    pixmap.fill(Qt::black);
    pbtnColor->setIcon(QIcon(pixmap));
    connect(pbtnColor,SIGNAL(clicked()),this,
            SLOT(selectColor()));
    pbtnColor->setStyleSheet("margin-left:10px;");


    pbtnClearAll = new QToolButton(ptoolBar);
    pbtnClearAll->setText("clear all");
    pbtnClearAll->setStyleSheet("border: 1px solid grey;");
    connect(pbtnClearAll,SIGNAL(clicked()),this,
            SLOT(btnClearAll()));
    pbtnClearAll->setStyleSheet("QToolButton {"
                                "margin-left:10px;"
                              "background-color: #4CAF50; /* 背景颜色 */"
                              "border: 2px solid #008CBA; /* 边框样式 */"
                              "color: white; /* 文本颜色 */"
                              "padding: 5px 10px; /* 内边距 */"
                              "border-radius: 5px; /* 边框圆角 */"
                              "}");


    ptoolBar->addWidget(plabelLineStyle);
    ptoolBar->addWidget(pcomboBoxLineStyle);
    ptoolBar->addWidget(plabelLineWidth);
    ptoolBar->addWidget(pspinBoxLineWidth);
    ptoolBar->addWidget(pbtnColor);
    ptoolBar->addWidget(pbtnClearAll);
//    ptoolBar->setStyleSheet("spacing:10px;");

    addToolBar(ptoolBar);
}


void MainWindow::btnClearAll()
{
    pDrawWidget->clearArtboard();
}

MainWindow::~MainWindow()
{
}

