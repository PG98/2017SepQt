#ifndef DATA_H
#define DATA_H
#include<QSqlQuery>
#include "dish.h"
#include <QVariant>
class Data{
public:
    Data(){}
    static int a;
    static Dish dish[50];
    static void dataInit();
};



#endif // DATA_H
