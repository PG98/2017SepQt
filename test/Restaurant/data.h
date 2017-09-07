#ifndef DATA_H
#define DATA_H
#include<QSqlQuery>

class Data{
public:
    static int a;
    static int dishname;
    static void dataInit();
};

int Data::a=0;
int Data::dishname=0;
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
    query.exec("select * from dish");
    while(query.next()){
        if(query.value(2).toString()=="beef"){
            dishname=query.value(3).toInt();
            break;
        }
    }
}

#endif // DATA_H
