#ifndef TABLE_H
#define TABLE_H

class Table{
public:
    Table(){}
    int id;
    int customerID;
    int waiterIndex = -1;
    int volume;
    bool water = false;
    int remind = -1;
    bool pay = false;
    int state; //0为空闲 -1等待服务  大于0：被id为state的服务员接管
};

#endif // TABLE_H
