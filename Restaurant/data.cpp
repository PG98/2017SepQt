#include "data.h"
#include <QDebug>

Dish Data::dish[100];
User Data::user[100];

void Data::dataInit(){
    QSqlQuery query;
    int i=0;
    query.prepare("select * from user");
    query.exec();
    while(query.next()){
        qDebug()<<query.value(2).toString();
        user[i].id = query.value(0).toInt();
        user[i].pwd = query.value(1).toString();
        user[i].phone = query.value(2).toString();
        user[i].email = query.value(3).toString();
        user[i].isMember = query.value(4).toInt();
        i++;
    }
    User::count = i;
    //初始化菜单
    query.prepare("select * from dish");
    query.exec();
    i=0;
    while(query.next()){
        dish[i].id = query.value(0).toInt();
        dish[i].type = DishType(query.value(1).toInt());
        dish[i].name = query.value(2).toString();
        dish[i].demand = query.value(3).toInt();
        dish[i].undone = query.value(4).toInt();
        dish[i].price = query.value(5).toInt();
        dish[i].notes = query.value(6).toString();
        i++;
    }
    Dish::count = i;
}

