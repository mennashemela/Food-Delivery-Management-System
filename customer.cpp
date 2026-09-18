//nadeen mohamed farid 20245070 g6
//yassin nabil mohamed 20245076 g7

#include "customer.h"

customer::customer(): user(){deliveryAddress="";
    loyaltyPoints=0;}

customer::customer(const string &id, const string &n, const string &p, const string &d, int l): user(id, n, p)
{deliveryAddress=d;
    loyaltyPoints=l;}


void customer::displayinfo()const{cout << "\n=== CUSTOMER INFO ===\n";
    cout << "ID : " << userid << endl;
    cout << "Name : " << name << endl;
    cout << "Phone : " << phonenumber << endl;
    cout << "Address : " << deliveryAddress << endl;
    cout << "Loyalty Points : " << loyaltyPoints << endl;
    cout << "Earnings : " << CalculateEarning() << endl;}


double customer::CalculateEarning()const{return loyaltyPoints*0.5;}

void customer::setdeliveryaddress(const string &d){deliveryAddress=d;}
string customer::getdeliveryaddress()const{return deliveryAddress;}


void customer::setloyaltypoints(int l){loyaltyPoints=l;}
int customer::getloyaltypoints() const { return loyaltyPoints; }


customer& customer::operator+=(int points){
    if (points > 0) {
        loyaltyPoints += points;}
    return *this;}