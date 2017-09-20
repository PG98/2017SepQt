#ifndef DATA_H
#define DATA_H
#include<QSqlQuery>
#include "dish.h"
#include "user.h"
#include "table.h"
#include "waiter.h"
#include "chef.h"
#include "orderinfo.h"
#include <QVariant>
#include <QList>
#include <QHash>

class Data{
public:
    Data(){}
    static QHash<int, User*> hash0;
    static QHash<int, Dish*> hash1;
    static Table table[10];
    static Waiter waiter[10];
    static Chef chef[10];
    static int orderCount;
    static int urgent[20];   // 催菜的订单号
    static QList<orderInfo*> list;
    static void dataInit();
};
#endif // DATA_H
