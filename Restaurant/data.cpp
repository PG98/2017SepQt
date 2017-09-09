#include "data.h"

int Data::a=0;

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
}

