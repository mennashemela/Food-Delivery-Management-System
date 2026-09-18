//nadeen mohamed farid 20245070 g6
//yassin nabil mohamed 20245076 g7

#include "user.h"
#include <string>

using namespace std;

class deliveryDriver : public user{
private:
    string vehicleType;
    int completedDeliveries;
    double totalEarnings;

public:

    deliveryDriver();

    deliveryDriver(const string &id , const string &n ,const string &p ,const string &v , int c , double e);

    void displayinfo() const;

    double CalculateEarning()const;

    void completeDelivery(double ordervalue);


    deliveryDriver& operator++();

    deliveryDriver operator++(int);


    string getvehicleType();
    int getcompletedDeliveries();
    double gettotalEarnings();
};