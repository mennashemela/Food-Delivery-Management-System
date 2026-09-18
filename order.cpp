//nadeen mohamed farid 20245070 g6
//yassin nabil mohamed 20245076 g7
#include "order.h"
#include "ENUMS.h"
#include <fstream>
#include <chrono>

int order::totalOrders = 0;

string orderStatusToString(OrderStatus status) {
    switch (status) {
        case OrderStatus::PENDING:
            return "PENDING";
        case OrderStatus::PREPARING:
            return "PREPARING";
        case OrderStatus::OUT_FOR_DELIVERY:
            return "OUT_FOR_DELIVERY";
        case OrderStatus::DELIVERED:
            return "DELIVERED";
        case OrderStatus::CANCELLED:
            return "CANCELLED";}
    return "UNKNOWN";}


order::order(){orderId="";
    Customer=nullptr;
    driver=nullptr;
    itemCount=0;
    capacity=5;
    status=OrderStatus::PENDING;
    items= new FoodItem[capacity];
    totalOrders++; }


order::order(const string&id , customer * c){orderId=id;
    Customer=c;
    driver=nullptr;
    itemCount=0;
    capacity=5;
    status=OrderStatus::PENDING;
    items= new FoodItem[capacity];
    totalOrders++; }

order::order(const order & other){
    orderId=other.orderId;
    Customer=other.Customer;
    driver=other.driver;
    items=nullptr;
    itemCount=other.itemCount;
    capacity=other.capacity;
    status=other.status;
    items = new FoodItem[capacity];
    for (int i = 0; i < itemCount; i++) {
        items[i] = other.items[i];}
    totalOrders++;}


order::~order(){delete[]items;
    totalOrders--;}


void order::reSizeArray(){
    if (capacity == 0) {capacity = 2;}
    else
        capacity *= 2;
    FoodItem* newitems = new FoodItem[capacity];
    for(int i=0; i<itemCount;i++){
        newitems[i]=items[i];}
    delete [] items;
    items= newitems;}


void order::additems(const FoodItem& item){
    if(itemCount>=capacity){reSizeArray();}
    items[itemCount++]=item;}

void order::assignDriver(deliveryDriver *drv){driver = drv ;}

void order::updateStatus(OrderStatus newStatus){
    status= newStatus;
    if (status == OrderStatus::DELIVERED) {double total = calculateTotal();
        if (driver){driver->completeDelivery(total);}
        if (Customer){ int points = total / 2;
            *Customer += points;
            cout<<"customer"<<Customer->getname() << " gained "<< points<< " loyalty points." <<endl;}}}

double order::calculateTotal()const{
    double total= 0.0;
    for(int i=0 ; i<itemCount ; i++){total+=items[i].CalculateItemTotal();}
    return total;}


void order::displayOrder() const {
    cout << "\n=================================================" << endl;
    cout << "Order Details: " << orderId<<endl;
    cout << "-------------------------------------------------" <<endl;
    cout << "Status: " << orderStatusToString(status) <<endl;
    cout << "Customer: " <<Customer->getname()<< endl;
    cout << "Driver: " <<driver->getname() <<endl;
    cout << "--- Items (" << itemCount << " total) ---" <<endl;
    for (int i = 0; i < itemCount; ++i) {cout << " ";
        items[i].displayitem();
        cout <<endl;}
    cout << "-------------------------------------------------" <<endl;
    cout << "ORDER TOTAL: " << calculateTotal() << " EGP" <<endl;
    cout << "=================================================" <<endl;}


OrderStatus order::getStatus() const { return status; }


int order::getTotalOrders(){
    return totalOrders ;}


order & order::operator +=(FoodItem & item){
    additems(item);
    return *this;}


order order::operator+(const order & other)const{
    string newID = this->orderId + "+" + other.orderId;
    order combined(newID,this->Customer);
    for (int i = 0; i < this->itemCount; i++){
        combined+=this->items[i];}
    for (int i = 0; i < other.itemCount; ++i) {
        combined+=other.items[i];}
    return combined;}


ostream & operator <<(ostream & os , const order & o){
    os << "Order ID: " << o.orderId << " | Status: " << orderStatusToString(o.status)
       << " Total: " << o.calculateTotal() << " EGP";
    if (o.Customer) {os << " Customer: " << o.Customer->getname();}
    if (o.driver) {os << " Driver: " << o.driver->getname();}
    return os; }


bool order::operator > (const order & o)const {
    return calculateTotal() > o.calculateTotal() ;}


FoodItem& order::operator [] (int index){
    if (index< 0 || index >= itemCount){
        cout<<"order item index out of boundries "<<endl;}
    return items[index];}



const FoodItem& order::operator [] (int index) const{
    if (index< 0 || index >= itemCount){
        cout<<"order item index out of boundries"<<endl;}
    return items[index];}


string order::getorderId() const { return orderId; }
customer* order::getcustomer() const { return Customer; }
deliveryDriver* order::getdriver() const { return driver; }

