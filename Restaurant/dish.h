#ifndef DISH_H
#define DISH_H
#include<QString>

enum DishType {Mainfood=1,Seafood,Vege,Soup,Dessert};
class Dish{
    DishType type;
    QString dishName;
    int id;
    int price;
    QString notes;
};

#endif // DISH_H
