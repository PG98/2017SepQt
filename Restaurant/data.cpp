#include "data.h"
#include <QDebug>

QHash<int, Dish*> Data::hash1;
QHash<int, User*> Data::hash0;
Waiter Data::waiter[10];
Chef Data::chef[10];
Table Data::table[10];
int Data::orderCount = 0;
int Data::urgent[20];
QList<orderInfo*> Data::list;

void Data::dataInit(){
    qDebug()<<"Data initialize.........";
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
        d->rating = query.value(8).toDouble();
        d->history = query.value(9).toInt();
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
        table[i].customerID = query.value(3).toInt();
        table[i].water = query.value(4).toInt();
        table[i].remind = query.value(5).toInt();
        table[i].pay = query.value(6).toInt();
        table[i].waiterIndex = query.value(7).toInt();
        i++;
    }
    //员工账号
    i=0;
    query.exec("select * from waiter");
    while(query.next()){
        waiter[i].id = query.value(0).toInt();
        waiter[i].table1 = query.value(1).toInt();
        waiter[i].table2 = query.value(2).toInt();
        waiter[i].rating = query.value(3).toDouble();
        waiter[i].history = query.value(4).toInt();
        i++;
    }
    i=0;
    query.exec("select * from chef");
    while(query.next()){
        chef[i].id = query.value(0).toInt();
        chef[i].history = query.value(1).toInt();
        i++;
    }
    for(int i=0;i<20;i++){
        urgent[i]=0;
    }
}

