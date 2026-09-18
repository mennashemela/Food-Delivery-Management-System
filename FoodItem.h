//nadeen mohamed farid 20245070 g6
//yassin nabil mohamed 20245076 g7


#include <iostream>
#include <string>

using namespace std;

class FoodItem {

private:
    string itemname;
    double price ;
    int quantity ;

public:

    FoodItem();
    FoodItem(string i , double p , int q);

    void setitemname(string i);
    string getitemname();

    void setprice(double p);
    double getprice();

    void setquantity(int q);
    int getquantity();


    double CalculateItemTotal() const;

    void displayitem() const;
};
