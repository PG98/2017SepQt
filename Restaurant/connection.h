#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection(){
    //如果.db文件已存在，select;否则create。
    QString select_table = "select tbl_name name from sqlite_master where type = 'table'";
    //对顾客账户的数据库操作命令
    QString select_max_user = "select max(id) from user";        //在register中用到
    QString insert_user = "insert into user values (?, ?, ?, ?, ?)";
    QString select_phone = "select phone from user";
    //对菜单的数据库操作命令
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
                query.exec("create table user (id int primary key, pwd varchar(30), phone varchar(30), email varchar(30), isMember int)");
                query.exec("insert into user values( 0, '123456', 10001', user0@gmail.com', 0)");
                query.exec("insert into user values( 1, '123456', 10002', user1@gmail.com', 0)");
                query.exec("insert into user values( 2, '123456', 10003', user2@gmail.com', 0)");
                query.exec("insert into user values( 3, '123456', 10004', user3@gmail.com', 0)");
                query.exec("insert into user values( 4, '123456', 10005', user4@gmail.com', 0)");
                query.exec("insert into user values( 5, '123456', 10006', user5@gmail.com', 0)");
                query.exec("insert into user values( 6, '123456', 10007', user6@gmail.com', 0)");
                query.exec("insert into user values( 7, '123456', 10008', user7@gmail.com', 0)");
                query.exec("insert into user values( 8, '123456', 10009', user8@gmail.com', 0)");
                query.exec("insert into user values( 9, '123456', 10010', user9@gmail.com', 0)");
                query.exec("insert into user values( 10, '123456', 10011', user10@gmail.com', 0)");
                query.exec("insert into user values( 11, '123456', 10012', user11@gmail.com', 0)");
                query.exec("insert into user values( 12, '123456', 10013', user12@gmail.com', 0)");
                query.exec("insert into user values( 13, '123456', 10014', user13@gmail.com', 0)");
                query.exec("insert into user values( 14, '123456', 10015', user14@gmail.com', 0)");
                query.exec("insert into user values( 15, '123456', 10016', user15@gmail.com', 0)");
                query.exec("insert into user values( 16, '123456', 10017', user16@gmail.com', 0)");
                query.exec("insert into user values( 17, '123456', 10018', user17@gmail.com', 0)");
                query.exec("insert into user values( 18, '123456', 10019', user18@gmail.com', 0)");
                query.exec("insert into user values( 19, '123456', 10020', user19@gmail.com', 0)");
                query.exec("insert into user values( 20, '123456', 10021', user20@gmail.com', 0)");
                query.exec("insert into user values( 21, '123456', 10022', user21@gmail.com', 0)");
                query.exec("insert into user values( 22, '123456', 10023', user22@gmail.com', 0)");
                query.exec("insert into user values( 23, '123456', 10024', user23@gmail.com', 0)");
                query.exec("insert into user values( 24, '123456', 10025', user24@gmail.com', 0)");
                query.exec("insert into user values( 25, '123456', 10026', user25@gmail.com', 0)");
                query.exec("insert into user values( 26, '123456', 10027', user26@gmail.com', 0)");
                query.exec("insert into user values( 27, '123456', 10028', user27@gmail.com', 0)");
                query.exec("insert into user values( 28, '123456', 10029', user28@gmail.com', 0)");
                query.exec("insert into user values( 29, '123456', 10030', user29@gmail.com', 0)");
                //======================================
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
