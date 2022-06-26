#include "nmeaDirDialog.h"
#include "ui_nmeaDirDialog.h"
#include <QFileDialog>
#include <QDebug>
#include<QMessageBox>
#include <QSettings>

class initdialog;

NmeaDirDialog::NmeaDirDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NmeaDirDialog) {
    ui->setupUi(this);
    connect(ui->browseButton, &QToolButton::clicked, this, &NmeaDirDialog::browseFolder);
    connect(ui->okButton, &QPushButton::clicked, this, &NmeaDirDialog::onOkButtonClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &NmeaDirDialog::close);
}

NmeaDirDialog::~NmeaDirDialog() {
    delete ui;
}

/* select a directory using file dialog */
void NmeaDirDialog::browseFolder() {
        QString path = QFileDialog::getExistingDirectory (this, tr("Directory"));
        if (!path.isNull()) {
            ui->lineEdit->setText(path);
            ui->okButton->setEnabled(true);
        }
}

void NmeaDirDialog::onOkButtonClicked() {
    QString path = ui->lineEdit->text();
    if (path.isEmpty()) {
        QMessageBox::information(this, tr("My Application"),
                                       tr("You have to select a folder."),
                                       QMessageBox::Ok);
    } else {
        QSettings settings;
        settings.setValue("NMEAfileLocation", path);
        settings.sync();

        myInitDialog = new InitDialog();
        myInitDialog->show();
        myInitDialog->activateWindow();
        connect(myInitDialog, SIGNAL(showPreviousDialog()), this, SLOT(show()));
        this->hide();
    }
}

