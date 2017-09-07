#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection(){
    //如果.db文件已存在，select;否则create。
    QString select_table = "select tbl_name name from sqlite_master where type = 'table'";
    //对顾客账户的数据库操作命令
    QString create_user = "create table user (id int primary key, pwd varchar(30), phone varchar(30), email varchar(30), history int)";
    QString select_max_user = "select max(id) from user";        //在register中用到
    QString insert_user = "insert into user values (?, ?, ?, ?, ?)";
    QString select_phone = "select phone from user";
    //对菜单的数据库操作命令
    QString create_dish = "create table dish (id1 int primary key, int type, dishName varchar(40), int price, notes varchar(40)";
    QString select_max_dish = "select max(id) from dish";
    QString insert_dish ="insert into dish values (?, ?, ?, ?, ?)";

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("database.db");
    bool tableFlag=false;
    if(!database.open()){
        qDebug()<<database.lastError();
        qFatal("failed to connect");
        return false;
    }
    else{
        qDebug()<<"open success";
        QSqlQuery query;
        query.prepare(select_table);
        if(!query.exec()){
                    qDebug()<<query.lastError();
                }
                else{
                    QString tableName;
                    while(query.next()){
                        tableName = query.value(0).toString();
                        qDebug()<<tableName;
                        if(tableName.compare("user")){  //string比对相同返回0
                            tableFlag=false;
                            qDebug()<<"table user does not exist";
                        }
                        else{
                            tableFlag=true;
                            qDebug()<<"table user exists";
                        }
                    }
                }
        if(tableFlag==false)        //初次打开时table不存在
             {
                query.exec("create table user (id int primary key, pwd varchar(30), phone varchar(30), email varchar(30), history int)");
                query.exec("create table dish (id int primary key, type int, dishName varchar(40), price int, notes varchar(40))");
                query.exec("insert into dish values(101, 1, 'roast duck', 20, 'test101')");
                query.exec("insert into dish values(102, 1, 'beef', 20, 'notes for beef')");
                 if(!query.exec()){
                     qDebug()<<query.lastError();
                 }
                 else{
                     qDebug()<<"table created!";
                 }
             }
        //菜谱表单
        /*
        query.prepare();
        if(!query.exec()){
                    qDebug()<<query.lastError();
                }
                else{
                    QString tableName;
                    while(query.next()){
                        tableName = query.value(0).toString();
                        qDebug()<<tableName;
                        if(tableName.compare("dish")){  //string比对相同返回0
                            tableFlag=false;
                            qDebug()<<"table dish does not exist";
                        }
                        else{
                            tableFlag=true;
                            qDebug()<<"table exists";
                        }
                    }
                }
        if(tableFlag==false)        //初次打开时table不存在
             {
                 query.prepare(create_dish);
                 //query.exec("insert into dish values(1, 1, 'beef', 20, 'shit')");
                 //query.exec("insert into dish values(2, 1, 'goat', 20, 'shit')");

                 if(!query.exec()){
                     qDebug()<<query.lastError();
                 }
                 else{
                     qDebug()<<"table dish created!";
                 }
             }*/
    }
    return true;
}

#endif // CONNECTION_H
