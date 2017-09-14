#ifndef USER_H
#define USER_H
#include <QString>

class User{
public:
    User();
    User(int ID, QString Pwd, QString Phone, QString Name, int IsMember):id(ID), pwd(Pwd), phone(Phone), name(Name), isMember(IsMember){}
    int id;
    QString pwd;
    QString phone;
    QString name;
    int isMember;
    static int getCount(){return count;}
    static int count;
};

#endif // USER_H
