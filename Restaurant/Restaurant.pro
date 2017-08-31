#-------------------------------------------------
#
# Project created by QtCreator 2017-08-24T10:30:01
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Restaurant
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    registerdialog.cpp \
    logindialog.cpp \
    orderchart.cpp \
    adminwindow.cpp \
    menumanage.cpp \
    usermanage.cpp

HEADERS  += mainwindow.h \
    registerdialog.h \
    logindialog.h \
    orderchart.h \
    adminwindow.h \
    menumanage.h \
    usermanage.h

FORMS    += mainwindow.ui \
    registerdialog.ui \
    logindialog.ui \
    orderchart.ui \
    adminwindow.ui \
    menumanage.ui \
    usermanage.ui

RESOURCES += \
    images.qrc
