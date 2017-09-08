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
    menumanage.cpp \
    usermanage.cpp \
    admindialog.cpp \
    data.cpp

HEADERS  += mainwindow.h \
    registerdialog.h \
    logindialog.h \
    orderchart.h \
    menumanage.h \
    usermanage.h \
    admindialog.h \
    data.h \
    connection.h \
    dish.h

FORMS    += mainwindow.ui \
    registerdialog.ui \
    logindialog.ui \
    orderchart.ui \
    menumanage.ui \
    usermanage.ui \
    admindialog.ui

RESOURCES += \
    images.qrc
