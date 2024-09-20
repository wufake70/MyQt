#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QFileDialog>
#include <QDateTime>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>

class Dialog : public QDialog
{
    Q_OBJECT

    QLabel *plabel_filepath;
    QLabel *plabel_filesize;
    QLabel *plabel_filetime1;
    QLabel *plabel_filetime2;
    QLabel *plabel_filetime3;

    QLineEdit *pedit1;
    QLineEdit *pedit2;
    QLineEdit *pedit3;
    QLineEdit *pedit4;
    QLineEdit *pedit5;

    QPushButton *pselectfile_btn;
    QPushButton *pgetfileinfo_btn;

    QGroupBox *pgroupbox;
    QHBoxLayout *pHBoxLay;
    QCheckBox *pcheck1;
    QCheckBox *pcheck2;
    QCheckBox *pcheck3;
    QCheckBox *pcheck4;
    QCheckBox *pcheck5;

    QGridLayout *pgridlay;

    void AnalyseFileAttri();
private slots:
    void SelectFile();
public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
};
#endif // DIALOG_H
