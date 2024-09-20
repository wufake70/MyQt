#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    resize(600,400);
    pFullPath = new QStack<QString>();
    pFullPath->push_back("/");
    pDirPathLineEdit = new QLineEdit("/",this);
    pListWidget = new QListWidget(this);
    pVBoxLay = new QVBoxLayout(this);
    pVBoxLay->addWidget(pDirPathLineEdit);
    pVBoxLay->addWidget(pListWidget);

    // 过滤当前盘符指定路径所有文件、文件夹(不递归)
    QFileInfoList list = (new QDir("/"))->entryInfoList(*new QStringList("*"), // 匹配规则
                                                        QDir::AllEntries,      // 文件/文件夹
                                                        QDir::DirsFirst);      // 排序规则
    DisplayFileInfoList(list);
    connect(pListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,
            SLOT(ShowDirItem(QListWidgetItem *)));
}

Dialog::~Dialog()
{
}

void Dialog::DisplayFileInfoList(QFileInfoList list)
{
    pListWidget->clear(); // 清除当前所有子控件
    QIcon icon;
    for(int i=0;i<list.count();i++)
    {
        QFileInfo temp = list[i];
        if(temp.isDir())
        {
            icon.addFile(":/new/prefix1/folder.png");
            pListWidget->addItem((new QListWidgetItem(icon,temp.fileName())));

        }else{
            icon.addFile(":/new/prefix1/file.png");
            pListWidget->addItem((new QListWidgetItem(icon,temp.fileName())));

        }
    }
}
void Dialog::ShowSubDir(QDir dir)
{
    DisplayFileInfoList(dir.entryInfoList(*new QStringList("*"),QDir::AllEntries,QDir::DirsFirst));
}
void Dialog::ShowDirItem(QListWidgetItem *item)
{
    QString fullPath;
    if(item->text()=="."){
        return ;
    }else if(item->text()==".."){
        pFullPath->pop();
        for(int i=0;i<pFullPath->size();i++)
        {
            fullPath.append(pFullPath[0][i]);
        }
//        std::reverse(fullPath.begin(),fullPath.end());
        pDirPathLineEdit->setText(fullPath);
        ShowSubDir(*new QDir(pDirPathLineEdit->text()));

    }else{
        pFullPath->push_back(item->text()+"/");
        for(int i=0;i<pFullPath->size();i++)
        {
            fullPath.append(pFullPath[0][i]);
        }
//        std::reverse(fullPath.begin(),fullPath.end());

        // folder or file
        if((new QFileInfo(fullPath))->isDir())
        {
            pDirPathLineEdit->setText(fullPath);
            ShowSubDir(*new QDir(fullPath));
        }
        else{
            pFullPath->pop();
//            pDirPathLineEdit->setText(fullPath);
        }
    }
}
