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
    registerdialog.cpp \
    logindialog.cpp \
    usermanage.cpp \
    admindialog.cpp \
    data.cpp \
    dish.cpp \
    order.cpp \
    menumanage.cpp \
    adddish.cpp \
    dishedit.cpp \
    user.cpp

HEADERS  += \
    registerdialog.h \
    logindialog.h \
    usermanage.h \
    admindialog.h \
    data.h \
    connection.h \
    dish.h \
    order.h \
    menumanage.h \
    adddish.h \
    dishedit.h \
    user.h

FORMS    += \
    registerdialog.ui \
    logindialog.ui \
    usermanage.ui \
    admindialog.ui \
    order.ui \
    menumanage.ui \
    adddish.ui \
    dishedit.ui

RESOURCES += \
    images.qrc

DISTFILES +=
