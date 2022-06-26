#-------------------------------------------------
#
# Project created by QtCreator 2012-11-25T21:38:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gps_emulator
TEMPLATE = app


macx: {
  # Copy the custom Info.plist to the app bundle
  plist.path = "$$DESTDIR/$$join(TARGET,,,.app)/Contents"
  plist.files = Info.plist
  QMAKE_INFO_PLIST = macos/Info.plist
  INSTALLS += plist

  ICON = macos/mapper_icon.icns
}

SOURCES += main.cpp\
    mainwindow.cpp \
    initdialog.cpp \
    nmeaDirDialog.cpp

HEADERS  += \
    mainwindow.h \
    initdialog.h \
    nmeaDirDialog.h

FORMS    += \
    mainwindow.ui \
    initdialog.ui \
    nmeaDirDialog.ui

RESOURCES += \
    resourses.qrc \
    resourses.qrc
