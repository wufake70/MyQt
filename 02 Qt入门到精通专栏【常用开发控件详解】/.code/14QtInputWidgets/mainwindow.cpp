#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QApplication>
#include <QMessageBox>
#include <QPushButton>


uint MainWindow::counts=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    counts++;
    ui->setupUi(this);

    pScreen = QApplication::primaryScreen();
    resize(pScreen->geometry().width()*0.5,
           pScreen->geometry().height()*0.5);

    TestComboBox();
    TestLineEdit();
    TestTextEdit();
    TestPlainEdit();
    TestSpinBox();
    TestDateTime();
    TestKeySequenceEdit();
}

void MainWindow::TestKeySequenceEdit()
{
    pWidget5 = new QWidget(this);
    pWidget5->setGeometry(width()/2,pWidget4->geometry().bottom()+10,200,100);
    pLabel4 = new QLabel("快捷键",pWidget5);
    pKeySequenceEdit = new QKeySequenceEdit(pWidget5);
    pKeySequenceEdit->move(pLabel4->geometry().left(),
                           pLabel4->geometry().bottom()+10);
    connect(pKeySequenceEdit,
            SIGNAL(keySequenceChanged(const QKeySequence&)),this,
            SLOT(shortcutkeyChanged(const QKeySequence&)));

}

void MainWindow::TestDateTime()
{
    pWidget4 = new QWidget(this);
    pWidget4->setGeometry(width()/2,pWidget3->geometry().bottom()+10,200,150);
    pDateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(),pWidget4);
    pDateEdit = new QDateEdit(QDate::currentDate(),pWidget4);
    pDateEdit->move(pDateTimeEdit->geometry().left(),
                    pDateTimeEdit->geometry().bottom()+10);
    pTimeEdit = new QTimeEdit(QTime::currentTime(),pWidget4);
    pTimeEdit->move(pDateEdit->geometry().left(),
                    pDateEdit->geometry().bottom()+10);
}


void MainWindow::TestSpinBox()
{
    pWidget3 = new QWidget(this);
    pWidget3->setGeometry(width()*0.5,
                          10,250,50);
    pWidget3->setStyleSheet("border:2px solid black;");
    pLabel3 = new QLabel("窗口透明度",pWidget3);

    pSpinBox = new QSpinBox(pWidget3);
    pSpinBox->move(pLabel3->width()+5,0);
    pSpinBox->setRange(20,100);
    pSpinBox->setSingleStep(5);
    pSpinBox->setSuffix("%不透明度");
    pSpinBox->setValue(100);
    connect(pSpinBox,SIGNAL(valueChanged(int)),this,SLOT(clickSpinBox(int)));

}
void MainWindow::TestPlainEdit()
{
    pWidget2 = new QWidget(this);
    pRadioBtn= new QRadioButton("只读模式",pWidget2);
    pPlainTextEdit = new QPlainTextEdit(pWidget2);
    pPlainTextEdit->move(0,pRadioBtn->geometry().bottom());
    pWidget2->move(0,pWidget1->geometry().bottom()+10);
    pWidget2->resize(200,150);
    pWidget2->setStyleSheet("border:2px solid black;");
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QFile fe("moc_mainwindow.cpp");
    fe.open(QFile::ReadOnly|QFile::Text);
    pTextStream = new QTextStream(&fe);
    pPlainTextEdit->insertPlainText(pTextStream->readAll());
    connect(pRadioBtn,SIGNAL(clicked()),this,SLOT(clickOnlyRead()));
}
void MainWindow::TestTextEdit()
{
    pWidget1 = new QWidget(this);
    pTextEdit = new QTextEdit(pWidget1);
    pWidget1->move(0,pWidget->geometry().bottom()+10);
    pWidget1->resize(200,100);
    pWidget1->setStyleSheet("border:2px solid black;");


}


void MainWindow::TestLineEdit()
{
    pWidget = new QWidget(this);

    pLineEdit = new QLineEdit(pWidget);
    QPushButton *pPushBtn = new QPushButton("click me",pWidget);
    pPushBtn->move(pPushBtn->geometry().right()+100,
                   pPushBtn->geometry().top());
    pLabel2 = new QLabel("content: ",pWidget);
    pLabel2->move(0,pPushBtn->geometry().bottom());

    pWidget->setGeometry(0,pLabel1->geometry().bottom()+10,
                         pPushBtn->geometry().right(),
                         100);
    connect(pPushBtn,SIGNAL(clicked()),this,SLOT(clickLineEdit()));
    pWidget->setStyleSheet("border: 2px solid black;");
    pWidget->findChildren<QWidget *>();
    for(auto i:pWidget->findChildren<QWidget *>())
    {
        i->setStyleSheet("border: 1px solid grey;");
    }

}

void MainWindow::TestComboBox()
{
    pComboBox = new QComboBox(this);
//    pComboBox->setFont(QFont("宋体"));
    pComboBox->addItem("logo");
    pComboBox->addItem("首页");
    pComboBox->addItem("题库");
    pComboBox->addItem("面试");
    pComboBox->addItem("简历");
    pComboBox->addItem("求职");
    pComboBox->addItem("学习");
    pComboBox->addItem("竞赛");

    connect(pComboBox,SIGNAL(activated(const QString)),this,SLOT(clickComboBox(const QString)));
    // 字体组合框
    pFontComboBox = new QFontComboBox(this);
    pFontComboBox->setGeometry(0,pComboBox->height(),
                               pFontComboBox->width(),
                               pFontComboBox->height());
    pLabel1 = new QLabel("字体组合框",this);
    pLabel1->setGeometry(0,pFontComboBox->geometry().bottom(),
                        pLabel1->width(),
                        pLabel1->height());
    connect(pFontComboBox,SIGNAL(currentFontChanged(QFont)),this,SLOT(clickFontComboBox(QFont)));
}

void MainWindow::clickComboBox(const QString &text)
{
    QMessageBox::information(this,"tips",text,0);
}

void MainWindow::clickFontComboBox(QFont font)
{
    pLabel1->setFont(font);
}
void MainWindow::clickLineEdit()
{
    pLabel2->setText("content:"+pLineEdit->text());
    pLabel2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    pLabel2->setWordWrap(true); // 如果文本很长，可以自动换行
    pLabel2->adjustSize(); // 调整 label2 的大小以适应文本内容
}
void MainWindow::clickOnlyRead()
{
    if(pRadioBtn->isChecked())
    {
        pPlainTextEdit->setReadOnly(true);
    }else{
        pPlainTextEdit->setReadOnly(false);
    }
}
void MainWindow::clickSpinBox(int x)
{
    this->setWindowOpacity((float)x/100);
}
void MainWindow::shortcutkeyChanged(const QKeySequence &keySequence)
{
    if(keySequence==QKeySequence(tr("Ctrl+Q")))
    {
        this->close();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

