#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T17:04:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pio_ui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    piowidget.cpp \
    mainwindow.cpp \
    ad7992.cpp \
    ch367.cpp \
    datamanager.cpp \
    scheduler.cpp

HEADERS += \
    piowidget.h \
    mainwindow.h \
    ad7992.h \
    ch367.h \
    datamanager.h \
    scheduler.h

INCLUDEPATH += $$PWD/CH367
LIBS += $$PWD/CH367/CH367DLL.lib

DISTFILES += \
    readme \
    ../../位移传感器程序结构图.vsd \
    位移传感器程序结构图.vsd
