//nadeen mohamed farid 20245070 g6
//yassin nabil mohamed 20245076 g7

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"
#include <string>

using namespace std;

class customer : public user{
private:
    string deliveryAddress;
    int loyaltyPoints;

public:
    customer();

    customer(const string &id, const string &n, const string &p, const string &d, int l);

    void displayinfo() const;

    double CalculateEarning() const;

    void setdeliveryaddress(const string &d);
    string getdeliveryaddress() const;


    void setloyaltypoints(int l);
    int getloyaltypoints() const;


    customer& operator+=(int points);
};

#endif