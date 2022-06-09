#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent, QString dirPath)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  dirPathPublic = dirPath; /*sets the path of the file in a public variable*/

  //    initialiazing values (coordinates, azimuth and altidude)
  Edeg = 23; Emin = 0.9783;
  Ndeg = 40; Nmin = 38.9562;
  angle = 000.0;
  alt = 022.11;

  showSent = -1; /*auxilliray variable initialization*/


  //    functionality of buttons
  connect(ui->startButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
  connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(onPauseButtonClicked()));
  connect(ui->sentButton, SIGNAL(clicked()), this, SLOT(onSentButtonClicked()));

  //    sets the timer which determines the coordinates production sequence
  connect(&timer, SIGNAL(timeout()), this, SLOT(moveDevice()));
  timer.start(1000);
}

void MainWindow::onSentButtonClicked() {
  showSent *= -1;

  if(showSent == 1) {
    ui->sentButton->setText("Show NMEA sentence");
    ui->textEdit->hide();
  } else {
    ui->sentButton->setText("Hide NMEA sentence");
    ui->textEdit->show();}
}

void MainWindow::onStartButtonClicked() {
  ui->pauseButton->setEnabled(true);
  ui->startButton->setEnabled(false);
  ui->modeLabel->setText("Moving");
}

void MainWindow::onPauseButtonClicked() {
  ui->startButton->setEnabled(true);
  ui->pauseButton->setEnabled(false);
  ui->modeLabel->setText("Static");
}

void MainWindow::moveDevice() {
  double dx, dy;
  if (ui->startButton->isEnabled()) {
    dx = 0; dy = 0;
  } else {
    dx   = qrand() % 9  * 0.0002;
    dy   = qrand() % 8  * 0.00014;
    alt += qrand() % 3   * 0.15;
  }

  double EminO = 0;
  EminO = Emin + dx;

  if (EminO >= 100) {
    Emin = EminO - 100;
    Edeg = Edeg + 1;
  } else
    Emin  = EminO;

  double NminO = 0;
  NminO = Nmin + dy;
  if (NminO >= 100) {
    Nmin = NminO - 100;
    Ndeg = Ndeg + 1;
  }
  else Nmin  = NminO;

  if (angle <= 359)
    angle = angle + 1;
  else angle = 001.0;

  QString str_Edeg, str_Emin, str_Ndeg, str_Nmin;
  QString str_angle, str_alt;

  str_Edeg = QString("%1").arg(Edeg,0,'f',0);
  if (Emin < 10)
    str_Emin = QString("0%1").arg(Emin,0,'f',4);
  else
    str_Emin = QString("%1").arg(Emin,0,'f',4);

  str_Ndeg = QString("%1").arg(Ndeg,0,'f',0);
  if (Nmin < 10)
    str_Nmin = QString("0%1").arg(Nmin,0,'f',4);
  else
    str_Nmin = QString("%1").arg(Nmin,0,'f',4);

  if(angle <= 9)
    str_angle = QString("00%1").arg(angle,0,'f',1);
  if(angle > 9 && angle <= 99)
    str_angle = QString("0%1").arg(angle,0,'f',1);
  if(angle > 99)
    str_angle = QString("%1").arg(angle,0,'f',1);

  if(alt < 10)
    str_alt = QString("00%1").arg(alt,0,'f',2);
  if(alt >= 10 && alt < 100)
    str_alt = QString("0%1").arg(alt,0,'f',2);
  if(alt >= 100)
    str_alt = QString("%1").arg(alt,0,'f',2);

  ui->EdegLineEdit->setText(str_Edeg);
  ui->EminLineEdit->setText(str_Emin);
  ui->NdegLineEdit->setText(str_Ndeg);
  ui->NminLineEdit->setText(str_Nmin);
  ui->hLineEdit->setText(str_alt);

  //    inserts the NMEA sentence both into the file and the textbox
  QFile data(dirPathPublic + "/NMEA.txt");
  if (data.open(QFile::WriteOnly | QFile::Append)) {
    QTextStream out(&data);
    QString NMEA_sentence = "$GPGGA,074747.00,4057.65,N,2277.55,E,2,05,2.9," + str_alt + ",M,36.6,M,1,0000*6D" + "\n"
                            + "$GPGSV,3,1,10,19,73,266,37,03,54,186,38,06,45,169,37,11,26,297,38*78" + "\n"
                            + "$GPGSV,3,1,10,19,73,266,37,03,54,186,38,06,45,169,37,11,26,297,38*78" + "\n"
                            + "$GPGSV,3,2,10,32,30,234,32,14,49,108,,22,43,051,,18,14,053,*77" + "\n"
                            + "$GPGSV,3,3,10,28,05,327,,20,03,238,*79" + "\n"
                            + "$GPRMC,074747.00,A,"+ str_Ndeg + str_Nmin +",N,0"+ str_Edeg + str_Emin + ",E,"
                            + str_angle + ",131.1,300309,04,E,D*23" + "\n";
    out << NMEA_sentence;
    ui->textEdit->setText(NMEA_sentence);
  }
}

MainWindow::~MainWindow() {
  delete ui;
}
