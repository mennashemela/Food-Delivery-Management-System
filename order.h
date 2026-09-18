//nadeen mohamed farid 20245070 g6
//yassin nabil mohamed 20245076 g7
#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include "customer.h"
#include "deliveryDriver.h"
#include "FoodItem.h"
#include "ENUMS.h"
#include <cstring>
#include <iomanip>
#include <sstream>

using namespace std;

class order{

private:
    string orderId ;
    customer *Customer ;
    deliveryDriver *driver ;
    FoodItem* items ;
    int itemCount ;
    int capacity ;
    OrderStatus status ;
    static int totalOrders ;

public:

    order();
    order(const string&id , customer * c);
    order(const order & other);
    ~order();

    void reSizeArray();
    void additems(const FoodItem& item);
    void assignDriver(deliveryDriver *drv);
    void updateStatus(OrderStatus newStatus);
    double calculateTotal()const;
    void displayOrder() const;
    OrderStatus getStatus() const;
    static int getTotalOrders();

    order & operator +=(FoodItem & item);
    order operator+(const order & other)const;
    friend ostream & operator <<(ostream & os , const order & o);
    bool operator > (const order & o)const;
    FoodItem& operator [] (int index);
    const FoodItem& operator [] (int index) const;

    string getorderId() const;
    customer* getcustomer() const;
    deliveryDriver* getdriver() const;
};

void saveCompletedOrders(order**orders,int count);
void saveDriverStatistics(deliveryDriver** drivers, int count);
void saveOrderToBinary(order** orders, int count, const string& filename);
void loadOrderByPosition(const string& filename, int position);

#endif