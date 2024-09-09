#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QCheckBox *pCheckBox;

private slots:
    void ClickCheckBox(int state);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
