#ifndef DATA_H
#define DATA_H
#include<QSqlQuery>
#include "dish.h"
#include "user.h"
#include "table.h"
#include <QVariant>
#include <QHash>

class Data{
public:
    Data(){}
    static QHash<int, User*> hash0;
    static QHash<int, Dish*> hash1;
    static Table table[10];
    static void dataInit();
};
#endif // DATA_H
