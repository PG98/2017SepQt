#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QWidget>
#include <QtWidgets>
#include <QPainter>
#include "registerdialog.h"
#include "admindialog.h"
#include "selecttable.h"

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

    void on_staffBtn_clicked();

private:
    AdminDialog *adminDlg;
    Ui::LoginDialog *ui;
    QSqlDatabase database;
    bool tableFlag;

    int userid;
    QString userpwd;
    QString userphone;
    QString username;
    int member;
    bool matchFlag = false;
    //数据库操作命令
    //如果.db文件已存在，select;否则create。
    QString select_table = "select tbl_name name from sqlite_master where type = 'table'";
    //对顾客账户的数据库操作命令
    QString create_user = "create table user (id int primary key, pwd varchar(30), phone varchar(30), name varchar(30), isMember int)";
    QString select_max_user = "select max(id) from user";        //在register中用到
    QString insert_user = "insert into user values (?, ?, ?, ?, ?)";
    QString select_phone = "select phone from user";
    //对菜单的数据库操作命令
    QString create_dish = "create table dish (id int primary key, int type, dishName varchar(40), int price, notes varchar(40)";
    QString select_max_dish = "select max(id) from dish";
    QString insert_dish ="insert into dish values (?, ?, ?, ?, ?)";

};

#endif // LOGINDIALOG_H
