#ifndef DIALOG_H
#define DIALOG_H

//#include <QtGui/QMainWindow>
#include <QDialog>
#include <QDir>
#include "initdialog.h"

class MainWindow;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    QString dirPath;
    ~Dialog();
    
private:
    Ui::Dialog *ui;
    QDir directory;
    InitDialog *myInitDialog;

private slots:
    void browseFolder();
    void returnPath();
    void onOkButtonClicked();
};

#endif // DIALOG_H
