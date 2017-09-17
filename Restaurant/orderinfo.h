#ifndef ORDERINFO_H
#define ORDERINFO_H
//记录点菜信息，以一道菜为单位
//厨师可查看总的list，并通过插入顺序呈现优先度；同一张桌子，内存中可通过QList迭代，数据库中可直接select
class orderInfo{
public:
    orderInfo(){}
    orderInfo(int t, int d, int s, int c):tableid(t), dishid(d), status(s), count(c){}
    int tableid;
    int dishid;
    int status; //-1等待厨师接单，0做菜中，1完成等待服务员上菜
    int count;  //份数
};

#endif // ORDERINFO_H
