#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!createConnection())
        return 1;

    LoginDialog login;
    login.show();

    return a.exec();
}
