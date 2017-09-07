#include "menumanage.h"
#include "ui_menumanage.h"
#include <QSqlQuery>
#include<QDebug>

MenuManage::MenuManage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuManage)
{
    ui->setupUi(this); 
}

MenuManage::~MenuManage()
{
    delete ui;
}

void MenuManage::on_motherfucker_clicked()
{
    QSqlQuery query;
    int newprice = (ui->lineEdit->text()).toInt();
    qDebug()<<"newprice: "<<newprice;
    //query.exec(("update dish set price=%1 where dishName= 'beef'").arg(newprice));
    query.prepare("update dish set price = :price where dishName= 'beef'");
    query.bindValue(":price",newprice);
    query.exec();
}
