#ifndef DATA_H
#define DATA_H
#include <QSqlQuery>
#include "dish.h"

class Data{
public:
    static int a;
    static void dataInit();
};

int Data::a=0;
void Data::dataInit(){
    QSqlQuery query;
    query.prepare("select * from user");
    query.exec();
    while(query.next()){
        if(query.value(2).toString()=="test"){
            a=query.value(0).toInt();
            break;
        }
    }
}


#endif // DATA_H
