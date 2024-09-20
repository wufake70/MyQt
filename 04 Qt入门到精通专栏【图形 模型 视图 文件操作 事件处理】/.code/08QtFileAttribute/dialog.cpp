#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    pgridlay = new QGridLayout(this);
    plabel_filepath = new QLabel("文件路径名:",this);
    plabel_filesize = new QLabel("文件大小:",this);
    plabel_filetime1 = new QLabel("文件创建时间:",this);
    plabel_filetime2 = new QLabel("最后修改时间:",this);
    plabel_filetime3 = new QLabel("最后访问时间:",this);

    pedit1 = new QLineEdit(this);
    pedit2 = new QLineEdit(this);
    pedit3 = new QLineEdit(this);
    pedit4 = new QLineEdit(this);
    pedit5 = new QLineEdit(this);
    pedit1->setReadOnly(true);
    pedit2->setReadOnly(true);
    pedit3->setReadOnly(true);
    pedit4->setReadOnly(true);
    pedit5->setReadOnly(true);

    pgridlay->addWidget(plabel_filepath,0,0);
    pgridlay->addWidget(plabel_filesize,1,0);
    pgridlay->addWidget(plabel_filetime1,2,0);
    pgridlay->addWidget(plabel_filetime2,3,0);
    pgridlay->addWidget(plabel_filetime3,4,0);

    pgridlay->addWidget(pedit1,0,1);
    pgridlay->addWidget(pedit2,1,1,1,2);
    pgridlay->addWidget(pedit3,2,1,1,2);
    pgridlay->addWidget(pedit4,3,1,1,2);
    pgridlay->addWidget(pedit5,4,1,1,2);

    pgroupbox = new QGroupBox("文件属性",this);
    pcheck1 = new QCheckBox("文件",pgroupbox);
    pcheck2 = new QCheckBox("隐藏",pgroupbox);
    pcheck3 = new QCheckBox("可读",pgroupbox);
    pcheck4 = new QCheckBox("可写",pgroupbox);
    pcheck5 = new QCheckBox("可执行",pgroupbox);
    pcheck1->setEnabled(false);
    pcheck2->setEnabled(false);
    pcheck3->setEnabled(false);
    pcheck4->setEnabled(false);
    pcheck5->setEnabled(false);


    pHBoxLay = new QHBoxLayout(this);
    pHBoxLay->addWidget(pcheck1);
    pHBoxLay->addWidget(pcheck2);
    pHBoxLay->addWidget(pcheck3);
    pHBoxLay->addWidget(pcheck4);
    pHBoxLay->addWidget(pcheck5);
    pgroupbox->setLayout(pHBoxLay);
    pgridlay->addWidget(pgroupbox,5,0,1,3);

    pselectfile_btn = new QPushButton("选择文件",this);
    pgridlay->addWidget(pselectfile_btn,0,2,1,1);

    connect(pselectfile_btn,SIGNAL(clicked()),this,SLOT(SelectFile()));
    setLayout(pgridlay);
}

Dialog::~Dialog()
{
}

void Dialog::SelectFile()
{
    pedit1->setText(QFileDialog::getOpenFileName());
    AnalyseFileAttri();
}

void Dialog::AnalyseFileAttri()
{
    QFileInfo fileinfo(pedit1->text());
    if(fileinfo.isFile())
    {
        pedit1->setToolTip(pedit1->text());

        pcheck1->setChecked(true);
        pedit2->setText(QString::number(fileinfo.size()) +"(B)");
        pedit3->setText(fileinfo.birthTime().toString());
        pedit4->setText(fileinfo.lastModified().toString());
        pedit5->setText(fileinfo.lastRead().toString());

        fileinfo.isHidden()?pcheck2->setChecked(true):pcheck2->setChecked(false);
        fileinfo.isReadable()?pcheck3->setChecked(true):pcheck3->setChecked(false);
        fileinfo.isWritable()?pcheck4->setChecked(true):pcheck4->setChecked(false);
        fileinfo.isExecutable()?pcheck5->setChecked(true):pcheck5->setChecked(false);

    }


}





















