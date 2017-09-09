#include "menumanage.h"
#include "ui_menumanage.h"
#include "variate.h"
#include <QDebug>
#include "data.h"

MenuManage::MenuManage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuManage)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(10);

    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"id"<<"种类"<<"名字"<<"单价"<<"备注");
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    //ui->tableWidget->setItem(0,0,new QTableWidgetItem(Data::a));
    qDebug()<<"str from variate.h:  "<<str;
    qDebug()<<"dish from variate:   "<<dish.id;
    qDebug()<<"a from data.h"<<Data::a;

}

MenuManage::~MenuManage()
{
    delete ui;
}
