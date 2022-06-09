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
#  VERSION = $${THE_APP_VERSION}.$${THE_APP_BUILD}
#  QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.12


  # Copy the custom Info.plist to the app bundle
  plist.path = "$$DESTDIR/$$join(TARGET,,,.app)/Contents"
  plist.files = Info.plist
  QMAKE_INFO_PLIST = macos/Info.plist
  INSTALLS += plist

  ICON = macos/mapper_icon.icns
}

SOURCES += main.cpp\
        dialog.cpp \
    mainwindow.cpp \
    initdialog.cpp

HEADERS  += dialog.h \
    mainwindow.h \
    initdialog.h

FORMS    += \
    dialog.ui \
    mainwindow.ui \
    initdialog.ui

RESOURCES += \
    resourses.qrc \
    resourses.qrc
