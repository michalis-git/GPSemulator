#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include <QDebug>
#include<QMessageBox>
class initdialog;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(browseFolder()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(onOkButtonClicked()));
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(close()));
}

void Dialog::browseFolder()
{
    /* select a directory using file dialog */
        QString path = QFileDialog::getExistingDirectory (this, tr("Directory"), directory.path());
        if ( path.isNull() == false )
        {
            directory.setPath(path);
            returnPath();

        }
}

/*get list of file from given directory and the append it to listWidget */
void Dialog::returnPath()
{
    dirPath = directory.path();
    ui->lineEdit->setText(dirPath);
    ui->okButton->setEnabled(true);
}

void Dialog::onOkButtonClicked()
{
    qDebug() << dirPath;
    if (ui->lineEdit->text().isEmpty())
    {
        int ret = QMessageBox::information(this, tr("My Application"),
                                       tr("You have to select a folder."),
                                       QMessageBox::Ok);

        switch (ret) {
           case QMessageBox::Ok:
               // OK was clicked
               break;
           default:
               // should never be reached
               break;
         }
    }
    else
    {
        myInitDialog = new InitDialog(0, dirPath);
        myInitDialog->show();
        myInitDialog->activateWindow();
        connect(myInitDialog, SIGNAL(showPreviousDialog()), this, SLOT(show()));
        this->hide();
    }
}

Dialog::~Dialog()
{
    delete ui;
}
