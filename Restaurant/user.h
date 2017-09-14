#ifndef USER_H
#define USER_H
#include <QString>

class User{
public:
    User();
    User(int ID, QString Pwd, QString Phone, QString Email, int IsMember):id(ID), pwd(Pwd), phone(Phone), email(Email), isMember(IsMember){}
    int id;
    QString pwd;
    QString phone;
    QString email;
    int isMember;

    static int count;
};

#endif // USER_H
