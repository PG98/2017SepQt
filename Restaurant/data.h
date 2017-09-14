#ifndef DATA_H
#define DATA_H
#include<QSqlQuery>
#include "dish.h"
#include "user.h"
#include <QVariant>
class Data{
public:
    Data(){}
    static Dish dish[100];
    static User user[100];
    static void dataInit();
};



#endif // DATA_H
