#ifndef NMEADIRDIALOG_H
#define NMEADIRDIALOG_H

#include <QDialog>
#include "initdialog.h"

class MainWindow;

namespace Ui {
    class NmeaDirDialog;
}

class NmeaDirDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NmeaDirDialog(QWidget *parent = 0);
    ~NmeaDirDialog();
    
private:
    Ui::NmeaDirDialog *ui;
    InitDialog *myInitDialog;

private slots:
    void browseFolder();
    void onOkButtonClicked();
};

#endif // NMEADIRDIALOG_H
