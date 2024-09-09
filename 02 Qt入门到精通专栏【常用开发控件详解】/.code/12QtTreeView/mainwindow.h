#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QTreeView> // 已手动导入
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QStandardItemModel *pStandardItemModel;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void InitTreeViewFunc(); // 初始化操作

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
