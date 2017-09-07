#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QtSql>
#include "logindialog.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = 0);
    ~RegisterDialog();

private:
    Ui::RegisterDialog *ui;
    QSqlDatabase database;
    //QSqlQuery类提供执行和操作的SQL语句的方法。
    //可以用来执行DML（数据操作语言）语句，如SELECT、INSERT、UPDATE、DELETE，
    //以及DDL（数据定义语言）语句，例如CREATE TABLE。
    bool tableFlag;
    int max_id;

private slots:
    void OKBtn_clicked();
    void CancelBtn_clicked();
    void receivedb(QSqlDatabase db);
};

#endif // REGISTERDIALOG_H
