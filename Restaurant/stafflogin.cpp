#include "stafflogin.h"
#include "ui_stafflogin.h"
#include "data.h"
#include "waiterwindow.h"
#include "chefwindow.h"
#include <QtSql>
#include "QtWidgets"

staffLogin::staffLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::staffLogin)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText(tr("服务员'2'开头，厨师'3'开头"));
}

staffLogin::~staffLogin()
{
    delete ui;
}

void staffLogin::on_waiterBtn_clicked()
{
    int id = ui->lineEdit->text().toInt(), IDcheck;
    bool flag = false;
    QSqlQuery query;
    QString waiterstring = QString("select * from waiter where id = %1").arg(id);
    query.exec(waiterstring);
    if(!query.exec(waiterstring)){    //查找数据库中对应的号码
            qDebug()<<query.lastError();
            flag = false;
    }
    else{
        while(query.next()){
            IDcheck = query.value(0).toInt();
            qDebug()<<"waiter id: "<<IDcheck;
        }
        if(id == IDcheck)
            flag =true;
        else
            flag = false;
    }
    if(flag){
        waiterWindow* w = new waiterWindow;
        w->id = id;
        w->show();
        this->close();
    }
    else{
        QMessageBox::warning(this, tr("警告"), tr("员工号不正确"));
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
    }
}

void staffLogin::on_waiterBtn_2_clicked()
{
    int id = ui->lineEdit->text().toInt(), IDcheck;
    QString chefstring = QString("select * from chef where id = %1").arg(id);
    bool flag = false;
    QSqlQuery query;
    query.exec(chefstring);
    if(!query.exec(chefstring)){    //查找数据库中对应的号码
            qDebug()<<query.lastError();
            flag = false;
    }
    else{
        while(query.next()){
            IDcheck = query.value(0).toInt();
            qDebug()<<"chef id: "<<IDcheck;
        }
        if(id == IDcheck)
            flag = true;
        else flag = false;
    }
    if(flag){
        chefWindow* w = new chefWindow;
        w->show();
        this->close();
    }
    else{
        QMessageBox::warning(this, tr("警告"), tr("员工号不正确"));
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
    }
}
