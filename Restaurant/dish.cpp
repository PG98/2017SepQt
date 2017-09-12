#include "dish.h"
int Dish::count = 0;

Dish::Dish(){
  id=6;
  name="";
  type=Main;
  demand=0;
  undone=false;
}

QString Dish::getType(){
    //enum DishType {Main=1,Cold, Seafood, Meat, Vege, Soup, Dessert, Drink};
    if(type == Main) return "主食";
    if(type == Cold) return "凉菜";
    if(type == Seafood) return "海鲜";
    if(type == Meat) return "荤菜";
    if(type == Vege) return "素菜";
    if(type == Soup) return "汤类";
    if(type == Dessert) return "点心";
    if(type == Drink) return "饮料";
    return "wrong";
}
