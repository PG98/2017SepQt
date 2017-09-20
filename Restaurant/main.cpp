#include <QApplication>
#include "logindialog.h"
#include "connection.h"
#include <QtSql>
#include <QDebug>
#include <QDate>
#include "data.h"

void saveJournal();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!createConnection())
        return 1;

    LoginDialog login;
    login.show();

    saveJournal();

    return a.exec();
}
//存储点菜列表中的信息作为账目
void saveJournal(){
    QSqlQuery query;
    QString tempstring;
    QDate date = QDate::currentDate();
    QString dateStr = date.toString("yyyy-MM-dd");
    for(orderInfo* info : Data::list){
        tempstring = "insert into journal values(?, ?, ?, ?, ?)";
        query.prepare(tempstring);
        query.addBindValue(info->tableid+1);
        query.addBindValue(Data::hash1[info->dishid]->name);
        query.addBindValue(Data::hash1[info->dishid]->price);
        query.addBindValue(info->count);
        query.addBindValue(dateStr);
        if(!query.exec()){
            qDebug()<<query.lastError();
        }
        else{
            qDebug()<<"inserted: "<<Data::hash1[info->dishid]->name;
        }
        query.next();
    }
    qDebug()<<"insert complete";
}
