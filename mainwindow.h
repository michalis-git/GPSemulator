#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, QString dirPath);
    ~MainWindow();
    QTimer initTimer;
    QTimer initDurationTimer;
    QTimer timer;
    bool route;
    int k;
    int l;
    int showSent;
    QString str_Edeg; QString str_Emin; QString str_Ndeg; QString str_Nmin;
    QString str_angle; QString str_alt;
    QString dirPathPublic;

private slots:
    void moveDevice();
    void onStartButtonClicked();
    void onPauseButtonClicked();
    void onSentButtonClicked();

private:
    Ui::MainWindow *ui;

    //QString *text;
    double E;
    double N;
    double Edeg, Emin, Ndeg, Nmin;
    double angle;
    double alt;
    int met;
    int counter;
    //int pj_transform( projPJ srcdefn, projPJ dstdefn, long point_count, int point_offset, double *x, double *y, double *z );
    //QList<QString> list;
};

#endif // MAINWINDOW_H
