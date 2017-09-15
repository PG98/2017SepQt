#include "stafflogin.h"
#include "ui_stafflogin.h"
#include "data.h"
#include "waiterwindow.h"
#include <QtSql>
#include "QtWidgets"

staffLogin::staffLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::staffLogin)
{
    ui->setupUi(this);

    connect(ui->lineEdit, SIGNAL(returnPressed()), ui->loginBtn, SIGNAL(clicked()), Qt::UniqueConnection);   //回车绑定登陆按钮

}

staffLogin::~staffLogin()
{
    delete ui;
}

void staffLogin::on_loginBtn_clicked()
{
    int id = ui->lineEdit->text().toInt();
    bool flag = true;
    QSqlQuery query;
    QString tempstring = QString("select * from waiter where id = %1").arg(id);
    query.exec(tempstring);
    if(!query.exec(tempstring)){    //查找数据库中对应的号码
            qDebug()<<query.lastError();
            flag = false;
    }
    if(flag){
        waiterWindow* w = new waiterWindow;
        w->show();
        this->close();
    }
    else{
        QMessageBox::warning(this, tr("警告"), tr("员工号不正确"));
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
    }


}
