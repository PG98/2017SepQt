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
                        /*
                        if(tableName.compare("user")){  //string比对相同返回0
                            tableFlag=false;
                            qDebug()<<"table does not exist";
                        }
                        else{
                            tableFlag=true;
                            qDebug()<<"table exists";
                        }*/
                    }
                }
        if(tableFlag==false)        //初次打开时table不存在
             {
                query.exec("create table user (id int primary key, pwd varchar(30), phone varchar(30), name varchar(30), isMember int)");
                query.exec("insert into user values( 100, '123456', '10001', 'user100', 0)");
                query.exec("insert into user values( 101, '123456', '10002', 'user101', 0)");
                query.exec("insert into user values( 102, '123456', '10003', 'user102', 1)");
                query.exec("insert into user values( 103, '123456', '10004', 'user103', 0)");
                query.exec("insert into user values( 104, '123456', '10005', 'user104', 0)");
                query.exec("insert into user values( 105, '123456', '10006', 'user105', 0)");
                query.exec("insert into user values( 106, '123456', '10007', 'user106', 1)");
                query.exec("insert into user values( 107, '123456', '10008', 'user107', 0)");
                query.exec("insert into user values( 108, '123456', '10009', 'user108', 0)");
                query.exec("insert into user values( 109, '123456', '10010', 'user109', 1)");
                query.exec("insert into user values( 110, '123456', '10011', 'user110', 0)");
                query.exec("insert into user values( 111, '123456', '10012', 'user111', 0)");
                query.exec("insert into user values( 112, '123456', '10013', 'user112', 1)");
                query.exec("insert into user values( 113, '123456', '10014', 'user113', 0)");
                query.exec("insert into user values( 114, '123456', '10015', 'user114', 0)");
                query.exec("insert into user values( 115, '123456', '10016', 'user115', 0)");
                query.exec("insert into user values( 116, '123456', '10017', 'user116', 1)");
                query.exec("insert into user values( 117, '123456', '10018', 'user117', 0)");
                query.exec("insert into user values( 118, '123456', '10019', 'user118', 1)");
                query.exec("insert into user values( 119, '123456', '10020', 'user119', 1)");
                query.exec("insert into user values( 120, '123456', '10021', 'user120', 0)");
                query.exec("insert into user values( 121, '123456', '10022', 'user121', 1)");
                query.exec("insert into user values( 122, '123456', '10023', 'user122', 0)");
                query.exec("insert into user values( 123, '123456', '10024', 'user123', 0)");
                query.exec("insert into user values( 124, '123456', '10025', 'user124', 1)");
                query.exec("insert into user values( 125, '123456', '10026', 'user125', 0)");
                query.exec("insert into user values( 126, '123456', '10027', 'user126', 0)");
                query.exec("insert into user values( 127, '123456', '10028', 'user127', 1)");
                query.exec("insert into user values( 128, '123456', '10029', 'user128', 0)");
                query.exec("insert into user values( 129, '123456', '10030', 'user129', 1)");
                //======================================
                query.exec("create table dish (id int primary key, type int, dishName varchar(40), demand int,undone int, price int, notes varchar(40), special int, rating real, history int)");
                query.exec("insert into dish values(201, 2, '酱萝卜', 0, 0, 10, 'null', 0, 5, 0)");
                query.exec("insert into dish values(202, 2, '话梅芸豆', 0, 0, 12, 'null', 0, 5, 0)");
                query.exec("insert into dish values(203, 2, '泡椒木耳', 0, 0, 10, 'null', 0, 5, 0)");
                query.exec("insert into dish values(204, 2, '原味蛤肉', 0, 0, 22, 'null', 0, 5, 0)");
                query.exec("insert into dish values(205, 2, '白切羊肉', 0, 0, 38, 'null', 0, 5, 0)");
                query.exec("insert into dish values(206, 2, '泰式凤爪', 0, 0, 28, 'null', 0, 5, 0)");
                query.exec("insert into dish values(301, 3, '澳洲龙虾', 0, 0, 85, 'null', 1, 5, 0)");
                query.exec("insert into dish values(302, 3, '象拔蚌', 0, 0, 50, 'null', 1, 5, 0)");
                query.exec("insert into dish values(303, 3, '皮皮虾', 0, 0, 66, 'null', 1, 5, 0)");
                query.exec("insert into dish values(304, 3, '对虾', 0, 0, 35, 'null', 0, 5, 0)");
                query.exec("insert into dish values(305, 3, '梭子蟹', 0, 0, 70, 'null', 0, 5, 0)");
                query.exec("insert into dish values(306, 3, '大闸蟹', 0, 0, 80, 'null', 0, 5, 0)");
                query.exec("insert into dish values(307, 3, '文蛤', 0, 0, 40, 'null', 1, 5, 0)");
                query.exec("insert into dish values(401, 4, '跳水牛蛙', 0, 0, 38, 'null', 0, 5, 0)");
                query.exec("insert into dish values(402, 4, '干锅鸡杂', 0, 0, 38, 'null', 0, 5, 0)");
                query.exec("insert into dish values(403, 4, '鱼香肉丝', 0, 0, 26, 'null', 0, 5, 0)");
                query.exec("insert into dish values(404, 4, '干锅牛排', 0, 0, 68, 'null', 0, 5, 0)");
                query.exec("insert into dish values(405, 4, '板栗烧黄鳝', 0, 0, 88, 'null', 0, 5, 0)");
                query.exec("insert into dish values(406, 4, '啤酒鸭', 0, 0, 86, 'null', 1, 5, 0)");
                query.exec("insert into dish values(501, 5, '苦瓜', 0, 0, 16, 'null', 1, 5, 0)");
                query.exec("insert into dish values(502, 5, '西葫芦', 0, 0, 12, 'null', 0, 5, 0)");
                query.exec("insert into dish values(503, 5, '青椒土豆丝', 0, 0, 10, 'null', 0, 5, 0)");
                query.exec("insert into dish values(504, 5, '蚝油生菜', 0, 0, 12, 'null', 1, 5, 0)");
                query.exec("insert into dish values(505, 5, '油焖茄子', 0, 0, 15, 'null', 0, 5, 0)");
                query.exec("insert into dish values(506, 5, '空心菜', 0, 0, 15, 'null', 0, 5, 0)");
                query.exec("insert into dish values(601, 6, '三鲜汤', 0, 0, 18, 'null', 0, 5, 0)");
                query.exec("insert into dish values(602, 6, '番茄蛋汤', 0, 0, 10, 'null', 0, 5, 0)");
                query.exec("insert into dish values(603, 6, '酸辣羹', 0, 0, 22, 'null', 0, 5, 0)");
                query.exec("insert into dish values(701, 7, '小笼包', 0, 0, 28, 'null', 1, 5, 0)");
                query.exec("insert into dish values(702, 7, '汤圆', 0, 0, 28, 'null', 0, 5, 0)");
                query.exec("insert into dish values(703, 7, '榴莲酥', 0, 0, 28, 'null', 0, 5, 0)");
                query.exec("insert into dish values(704, 7, '奶黄木瓜酥', 0, 0, 28, 'null', 0, 5, 0)");
                query.exec("insert into dish values(801, 8, '柠檬水', 0, 0, 30, 'null', 0, 5, 0)");
                query.exec("insert into dish values(802, 8, '碧螺春', 0, 0, 50, 'null', 1, 5, 0)");
                query.exec("insert into dish values(803, 8, '茅台', 0, 0, 2000, 'null', 1, 5, 0)");
                query.exec("insert into dish values(804, 8, '五粮液', 0, 0, 1100, 'null', 1, 5, 0)");
                //===================================================
                query.exec("create table diningtable (id int primary key, volume int, state int, customerID int, water int, remind int, pay int, waiterid int)");//0空闲，-1等待服务，>0正在被服务
                query.exec("insert into diningtable values(1, 6, 0, 0, 0, 0, 0, 0)");
                query.exec("insert into diningtable values(2, 6, 0, 0, 0, 0, 0, 0)");
                query.exec("insert into diningtable values(3, 6, 0, 0, 0, 0, 0, 0)");
                query.exec("insert into diningtable values(4, 10, 0, 0, 0, 0, 0, 0)");
                query.exec("insert into diningtable values(5, 10, 0, 0, 0, 0, 0, 0)");
                query.exec("insert into diningtable values(6, 10, 0, 0, 0, 0, 0, 0)");
                query.exec("insert into diningtable values(7, 10, 0, 0, 0, 0, 0, 0)");
                query.exec("insert into diningtable values(8, 15, 0, 0, 0, 0, 0, 0)");
                query.exec("insert into diningtable values(9, 15, 0, 0, 0, 0, 0, 0)");
                query.exec("insert into diningtable values(10, 15, 0, 0, 0, 0, 0, 0)");
                //===================================================
                query.exec("create table waiter (id int primary key, table1 int, table2 int, comment real, history int)");
                query.exec("insert into waiter values(201, 0, 0, 5.0, 5)");
                query.exec("insert into waiter values(202, 0, 0, 5.0, 5)");
                query.exec("insert into waiter values(203, 0, 0, 5.0, 5)");
                query.exec("insert into waiter values(204, 0, 0, 5.0, 5)");
                query.exec("insert into waiter values(205, 0, 0, 5.0, 5)");
                //===================================================
                query.exec("create table chef (id int primary key, history int)");
                query.exec("insert into chef values(301, 5)");
                query.exec("insert into chef values(302, 5)");
                query.exec("insert into chef values(303, 5)");
                query.exec("insert into chef values(304, 5)");
                query.exec("insert into chef values(305, 5)");
                //====================================================
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
