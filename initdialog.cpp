#include "initdialog.h"
#include "ui_initdialog.h"
#include <QMessageBox>
#include <QTimer>
#include <QDebug>

class MainWindow;

InitDialog::InitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitDialog) {
    ui->setupUi(this);
    connect(ui->conButton, SIGNAL(clicked()), this, SLOT(onConButtonClicked()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(onBackButtonClicked()));
    counter = -1;
}

InitDialog::~InitDialog() {
    delete ui;
}

void InitDialog::onConButtonClicked() {
    ui->conButton->setEnabled(false);
    initDurationTimerOn();
    initTimerOn();
}

void InitDialog::onBackButtonClicked() {
    emit showPreviousDialog();
    this->close();
}

void InitDialog::initTimerOn() {
    connect(&initTimer, SIGNAL(timeout()), this, SLOT(changeStatus()));
    initTimer.start(1000);
}

void InitDialog::changeStatus() {
    counter=counter*(-1);
    if (counter>0)
        ui->statusLabel->setText("Initialize..");
    else
        ui->statusLabel->setText("Initialize....");
}

void InitDialog::initDurationTimerOn() {
    connect(&initDurationTimer, SIGNAL(timeout()), this, SLOT(statusConnected()));
    initDurationTimer.start(9000);
}

void InitDialog::statusConnected() {
    initTimer.stop();
    ui->statusLabel->setText("<font color=\"blue\">Connected!</font>");
    initDurationTimer.stop();
    int ret = QMessageBox::information(this, tr("My Application"),
                                       tr("You are now connected! Click OK"),
                                       QMessageBox::Ok);

    if (ret == QMessageBox::Ok) {
        myMainWindow = new MainWindow();
        myMainWindow->show();
        this->close();
    }
}
