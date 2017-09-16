#ifndef ORDERINFO_H
#define ORDERINFO_H

class orderInfo{
public:
    orderInfo(){}
    orderInfo(int t, int d, int s):tableid(t), dishid(d), status(s){}
    int tableid;
    int dishid;
    int status; //-1等待厨师接单，0做菜中，1完成等待服务员上菜
};



#endif // ORDERINFO_H
