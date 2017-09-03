#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QWidget>
#include <QtWidgets>
#include <QPainter>
#include "registerdialog.h"
#include "orderchart.h"
#include "admindialog.h"

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
    AdminDialog *adminDlg;
    Ui::LoginDialog *ui;
    QSqlDatabase database;
    bool tableFlag;

    int userid;
    QString userpwd;
    QString userphone;
    QString userEmail;
    int userHistory;
    bool matchFlag = false;
    //数据库操作命令
    //如果.db文件已存在，select;否则create。
    QString select_table = "select tbl_name name from sqlite_master where type = 'table'";
    QString create_sql = "create table user (id int primary key, pwd varchar(30), phone varchar(30), email varchar(30), history int)";
    QString select_max_sql = "select max(id) from user";        //在register中用到
    QString insert_sql = "insert into user values (?, ?, ?, ? ?)";
    QString select_sql = "select phone from user";
};

#endif // LOGINDIALOG_H
