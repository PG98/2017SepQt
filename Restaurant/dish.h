#ifndef DISH_H
#define DISH_H
#include <QString>

enum DishType {Main=1,Cold, Seafood, Meat, Vege, Soup, Dessert, Drink};
class Dish{
public:
    Dish();
    Dish(int ID,QString n,int t,int d,bool u,int p,QString nt):id(ID),name(n),type((DishType)t),demand(d),undone(u),price(p),notes(nt){}
    int id;
    QString name;
    DishType type;
    int demand;
    bool undone;
    int price;
    QString notes;
    //以上和数据库列名对应
    QString getType();
    static int count;
};
/*
Dish::Dish(){
  id=8;
  name="";
  type=Main;
  demand=0;
  undone=false;
}
*/


#endif // DISH_H
