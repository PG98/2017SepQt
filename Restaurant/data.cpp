#include "data.h"

int Data::a=0;
Dish Data::dish[50];

void Data::dataInit(){
    QSqlQuery query;
    query.prepare("select * from user");
    query.exec();
    while(query.next()){
        if(query.value(1).toString()=="test"){
            a=query.value(0).toInt();
            break;
        }
    }

    query.prepare("select * from dish");
    query.exec();
    int i=0;
    while(query.next()){
        dish[i].id = query.value(0).toInt();
        dish[i].type = DishType(query.value(1).toInt());
        dish[i].name = query.value(2).toString();
        dish[i].price = query.value(3).toInt();
        dish[i].demand = query.value(4).toInt();
        dish[i].undone = query.value(4).toInt();
        dish[i].notes = query.value(4).toString();
        i++;
    }
}
