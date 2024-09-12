#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSplitter *pSplitter1;
    QSplitter *pSplitter2;
    QSplitter *pSplitter3;

    QTextEdit *pTextEdit1;
    QTextEdit *pTextEdit2;
    QTextEdit *pTextEdit3;
    QTextEdit *pTextEdit4;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
