#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QFontComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QDir>
#include <QRadioButton>
#include <QSpinBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>
#include <QKeySequenceEdit> // 快捷键

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QScreen *pScreen;
    QComboBox *pComboBox;
    QFontComboBox *pFontComboBox;
    QLabel *pLabel1;
    QLabel *pLabel2;
    QLabel *pLabel3;
    QLabel *pLabel4;
    QLineEdit *pLineEdit;
    QTextEdit *pTextEdit;
    QPlainTextEdit *pPlainTextEdit;
    QRadioButton *pRadioBtn;
    QTextStream *pTextStream;
    QDateTimeEdit *pDateTimeEdit;
    QTimeEdit *pTimeEdit;
    QDateEdit *pDateEdit;
    QSpinBox *pSpinBox;
    QKeySequenceEdit *pKeySequenceEdit;
    static uint counts;
    QWidget *pWidget;
    QWidget *pWidget1;
    QWidget *pWidget2;
    QWidget *pWidget3;
    QWidget *pWidget4;
    QWidget *pWidget5;

private slots:
    void clickComboBox(const QString &text);
    void clickFontComboBox(QFont font);
    void clickLineEdit();
    void clickOnlyRead();
    void clickSpinBox(int);
    void shortcutkeyChanged(const QKeySequence &keySequence);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void TestComboBox();
    void TestLineEdit();
    void TestTextEdit();
    void TestPlainEdit();
    void TestSpinBox();
    void TestDateTime();
    void TestKeySequenceEdit();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
