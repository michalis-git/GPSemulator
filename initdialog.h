#ifndef INITDIALOG_H
#define INITDIALOG_H

#include <QDialog>
#include <QTimer>
#include "mainwindow.h"

namespace Ui {
class InitDialog;
}

class InitDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InitDialog(QWidget *parent = nullptr);
    ~InitDialog();
    QTimer initTimer;
    QTimer initDurationTimer;
    QTimer timer;

    
private:
    Ui::InitDialog *ui;
    MainWindow *myMainWindow;
    int counter;

signals:
    void showPreviousDialog();

private slots:
    void onConButtonClicked();
    void onBackButtonClicked();
    void changeStatus();
    void initDurationTimerOn();
    void initTimerOn();
    void statusConnected();
};

#endif // INITDIALOG_H
