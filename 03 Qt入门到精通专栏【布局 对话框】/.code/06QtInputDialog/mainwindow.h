#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QInputDialog>
#include <QGridLayout>
#include <QWidget>
#include <QMouseEvent>
#include <QtDebug>

class MyLabel: public QLabel
{
public:
    MyLabel(QWidget *parent=nullptr):QLabel(parent){};
    MyLabel(QString str,QWidget *parent=nullptr):QLabel(parent)
    {
        this->setText(str);
        this->setStyleSheet("QLabel {"
                          "background-color: #4CAF50;"
                          "color: white;"
                          "padding: 8px 16px;"
                          "border: 1px solid #4CAF50;"
                          "border-radius: 4px;"
                          "}");
    };
protected:

    virtual void mousePressEvent(QMouseEvent *e) override;


};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *pCenterWidget;
    QLineEdit *plineEdit1;
    QLineEdit *plineEdit2;
    QLineEdit *plineEdit3;
    QLineEdit *plineEdit4;
    QPushButton *ppushBtn1;
    QPushButton *ppushBtn2;
    QPushButton *ppushBtn3;
    QPushButton *ppushBtn4;
    QGridLayout* pgridLay;

private slots:
    void clickNameBtn();
    void clickGenderBtn();
    void clickIdBtn();
    void clickScoreBtn();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
