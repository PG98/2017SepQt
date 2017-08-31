#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QWidget>
#include <QtWidgets>
#include <QPainter>
#include "registerdialog.h"
#include "orderchart.h"
#include "adminwindow.h"
#include "mainwindow.h" //test

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

signals:
    void transmitdb(QSqlDatabase db);

private slots:
    void login_clicked();
    void register_clicked();
    void getUserInfo(QString phone);

private:
    Ui::LoginDialog *ui;
    QSqlDatabase database;
    bool tableFlag;

    int userid;
    QString userpwd;
    QString userphone;
    QString userEmail;
    int userHistory;
    bool matchFlag;

    QString select_table = "select tbl_name name from sqlite_master where type = 'table'";
    QString create_sql = "create table user (id int primary key, pwd varchar(30), phone varchar(30), email varchar(30), history int)";
    QString select_max_sql = "select max(id) from user";
    QString insert_sql = "insert into user values (?, ?, ?, ? ?)";
    QString select_sql = "select phone from user";
};

#endif // LOGINDIALOG_H
