#include "data.h"
#include <QDebug>

QHash<int, Dish*> Data::hash1;
QHash<int, User*> Data::hash0;
Table Data::table[10];

void Data::dataInit(){
    QSqlQuery query;
    int i=0;
    query.prepare("select * from user");
    query.exec();
    while(query.next()){
        User* u = new User;
        u->id = query.value(0).toInt();
        u->pwd = query.value(1).toString();
        u->phone = query.value(2).toString();
        u->name = query.value(3).toString();
        u->isMember = query.value(4).toInt();
        hash0.insert(u->id, u);
        i++;
    }
    User::count = i;
    //初始化菜单
    i=0;
    query.prepare("select * from dish");
    query.exec();
    while(query.next()){
        Dish* d = new Dish;
        d->id = query.value(0).toInt();
        d->type = DishType(query.value(1).toInt());
        d->name = query.value(2).toString();
        d->demand = query.value(3).toInt();
        d->undone = query.value(4).toInt();
        d->price = query.value(5).toInt();
        d->notes = query.value(6).toString();
        d->special = query.value(7).toInt();
        hash1.insert(d->id, d);
        i++;
    }
    Dish::count = i;
    //餐桌
    i=0;
    query.exec("select * from diningtable");
    while(query.next()){
        table[i].id = query.value(0).toInt();
        table[i].volume = query.value(1).toInt();
        table[i].state = query.value(2).toInt();
        i++;
    }

    //员工账号
}

