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
    user.cpp \
    adduser.cpp \
    selecttable.cpp \
    stafflogin.cpp \
    chef.cpp \
    waiterwindow.cpp \
    chefwindow.cpp \
    staffmanage.cpp \
    orderquery.cpp \
    managerdialog.cpp \
    finishdialog.cpp

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
    user.h \
    adduser.h \
    selecttable.h \
    keybutton.h \
    stafflogin.h \
    chef.h \
    waiter.h \
    waiterwindow.h \
    chefwindow.h \
    table.h \
    orderinfo.h \
    staffmanage.h \
    orderquery.h \
    managerdialog.h \
    finishdialog.h

FORMS    += \
    registerdialog.ui \
    logindialog.ui \
    usermanage.ui \
    admindialog.ui \
    order.ui \
    menumanage.ui \
    adddish.ui \
    dishedit.ui \
    adduser.ui \
    selecttable.ui \
    stafflogin.ui \
    waiterwindow.ui \
    chefwindow.ui \
    staffmanage.ui \
    orderquery.ui \
    managerdialog.ui \
    finishdialog.ui

RESOURCES += \
    images.qrc

DISTFILES +=
