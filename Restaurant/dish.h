#ifndef DISH_H
#define DISH_H

enum DishType {Mainfood=1,Seafood,Vege,Soup,Dessert};
class Dish{
    DishType type=Mainfood;
    QString dishName="";
    int id=0;
    int price=0;
    QString notes="";
};

#endif // DISH_H
