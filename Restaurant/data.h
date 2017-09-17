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
    static Waiter waiter[5];
    static Chef chef[5];
    static int orderCount;
    static QList<orderInfo*> list;
    static void dataInit();
};
#endif // DATA_H
