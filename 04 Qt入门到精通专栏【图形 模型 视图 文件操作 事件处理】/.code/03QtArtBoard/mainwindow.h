#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QToolBar>
#include <QHBoxLayout>
#include "drawwidget.h"
#include <QSpinBox>
#include <QToolButton>
#include <QColorDialog>
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    ArtBoard *pDrawWidget;

    QLabel *plabelLineStyle;
    QComboBox *pcomboBoxLineStyle;

    QLabel *plabelLineWidth;
    QSpinBox *pspinBoxLineWidth;

    QToolButton *pbtnColor;
    QToolButton *pbtnClearAll;

    QToolBar *ptoolBar;

    void initDrawWidget();
    void initToolBar();
private slots:
    void selectLineStyle(int);
    void selectLineWidth(int);
    void selectColor();
    void btnClearAll();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
