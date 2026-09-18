//nadeen mohamed farid 20245070 g6
//yassin nabil mohamed 20245076 g7


#include "FoodItem.h"

FoodItem::FoodItem(){
    itemname="";
    price=0.0;
    quantity=0;}

FoodItem::FoodItem(string i , double p , int q){
    itemname=i;
    price=p;
    quantity=q;}

void FoodItem::setitemname(string i){itemname=i;}
string FoodItem::getitemname(){return itemname;}

void FoodItem::setprice(double p){price=p;}
double FoodItem::getprice(){return price;}

void FoodItem::setquantity(int q){quantity=q;}
int FoodItem::getquantity(){return quantity;}


double FoodItem::CalculateItemTotal() const {return quantity*price;}

void FoodItem::displayitem() const{cout<<itemname<<"x"<<quantity<<"@"<<price<<"Egp="<<CalculateItemTotal()<<"Egp"<<endl;}
