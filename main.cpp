#include "nmeaDirDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NmeaDirDialog w;
    w.show();
    
    return a.exec();
}
