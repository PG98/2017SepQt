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
                query.exec("create table dish (id int primary key, type int, dishName varchar(40), demand int,undone int, price int, notes varchar(40))");
                query.exec("insert into dish values(201, 2, '酱萝卜', 0, 0, 10, 'null')");
                query.exec("insert into dish values(202, 2, '话梅芸豆', 0, 0, 12, 'null')");
                query.exec("insert into dish values(203, 2, '泡椒木耳', 0, 0, 10, 'null')");
                query.exec("insert into dish values(204, 2, '原味蛤肉', 0, 0, 22, 'null')");
                query.exec("insert into dish values(205, 2, '白切羊肉', 0, 0, 38, 'null')");
                query.exec("insert into dish values(206, 2, '泰式凤爪', 0, 0, 28, 'null')");
                query.exec("insert into dish values(301, 3, '澳洲龙虾', 0, 0, 85, 'null')");
                query.exec("insert into dish values(302, 3, '象拔蚌', 0, 0, 50, 'null')");
                query.exec("insert into dish values(303, 3, '皮皮虾', 0, 0, 66, 'null')");
                query.exec("insert into dish values(304, 3, '对虾', 0, 0, 35, 'null')");
                query.exec("insert into dish values(305, 3, '梭子蟹', 0, 0, 70, 'null')");
                query.exec("insert into dish values(306, 3, '大闸蟹', 0, 0, 80, 'null')");
                query.exec("insert into dish values(307, 3, '文蛤', 0, 0, 40, 'null')");
                query.exec("insert into dish values(401, 4, '跳水牛蛙', 0, 0, 38, 'null')");
                query.exec("insert into dish values(402, 4, '干锅鸡杂', 0, 0, 38, 'null')");
                query.exec("insert into dish values(403, 4, '鱼香肉丝', 0, 0, 26, 'null')");
                query.exec("insert into dish values(404, 4, '干锅牛排', 0, 0, 68, 'null')");
                query.exec("insert into dish values(405, 4, '板栗烧黄鳝', 0, 0, 88, 'null')");
                query.exec("insert into dish values(406, 4, '啤酒鸭', 0, 0, 86, 'null')");
                query.exec("insert into dish values(501, 5, '苦瓜', 0, 0, 16, 'null')");
                query.exec("insert into dish values(502, 5, '西葫芦', 0, 0, 12, 'null')");
                query.exec("insert into dish values(503, 5, '青椒土豆丝', 0, 0, 10, 'null')");
                query.exec("insert into dish values(504, 5, '蚝油生菜', 0, 0, 12, 'null')");
                query.exec("insert into dish values(505, 5, '油焖茄子', 0, 0, 15, 'null')");
                query.exec("insert into dish values(506, 5, '空心菜', 0, 0, 15, 'null')");
                query.exec("insert into dish values(601, 6, '三鲜汤', 0, 0, 18, 'null')");
                query.exec("insert into dish values(602, 6, '番茄蛋汤', 0, 0, 10, 'null')");
                query.exec("insert into dish values(603, 6, '酸辣羹', 0, 0, 22, 'null')");
                query.exec("insert into dish values(701, 7, '小笼包', 0, 0, 28, 'null')");
                query.exec("insert into dish values(702, 7, '汤圆', 0, 0, 28, 'null')");
                query.exec("insert into dish values(703, 7, '榴莲酥', 0, 0, 28, 'null')");
                query.exec("insert into dish values(704, 7, '奶黄木瓜酥', 0, 0, 28, 'null')");
                query.exec("insert into dish values(801, 8, '柠檬水', 0, 0, 30, 'null')");
                query.exec("insert into dish values(802, 8, '碧螺春', 0, 0, 50, 'null')");
                query.exec("insert into dish values(803, 8, '茅台', 0, 0, 2000, 'null')");
                query.exec("insert into dish values(804, 8, '五粮液', 0, 0, 1100, 'null')");
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
