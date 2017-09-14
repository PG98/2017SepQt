#include "user.h"

int User::count = 0;

User::User(){
    id=0;
    isMember = 0;
}

void User::setUser(int ID, QString Pwd, QString Phone, QString Name, int IsMember){
    id = ID;
    pwd = Pwd;
    phone = Phone;
    name = Name;
    isMember = IsMember;
}
