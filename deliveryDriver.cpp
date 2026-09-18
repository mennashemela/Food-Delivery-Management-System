//nadeen mohamed farid 20245070 g6
//yassin nabil mohamed 20245076 g7


#include "deliveryDriver.h"

deliveryDriver::deliveryDriver():user(){completedDeliveries=0;
    totalEarnings=0.0;}

deliveryDriver::deliveryDriver(const string &id , const string &n ,const string &p ,const string &v , int c , double e): user(id,n,p)
{ vehicleType=v;
    completedDeliveries=c;
    totalEarnings=e;}


void deliveryDriver::displayinfo() const{
    cout << "\n=== DELIVERY DRIVER INFO ===\n";
    cout << "ID: " << userid << endl;
    cout << "Name: " << name << endl;
    cout << "Phone: " << phonenumber << endl;
    cout << "Vehicle: " << vehicleType << endl;
    cout << "Completed Deliveries: " << completedDeliveries << endl;
    cout << "Total Earnings: " << totalEarnings << " EGP" << endl;

    if (completedDeliveries > 0) {
        cout << "Average Earnings per Delivery:"<< (totalEarnings / completedDeliveries)<< " EGP\n";}
    else {cout << "there is no Average Earnings per Delivery";}}


double deliveryDriver::CalculateEarning()const{return totalEarnings;}

void deliveryDriver::completeDelivery(double ordervalue){totalEarnings+=ordervalue*0.15;
    completedDeliveries++;}


deliveryDriver& deliveryDriver::operator++() {
    completedDeliveries++;
    return *this;}

deliveryDriver deliveryDriver::operator++(int) {
    deliveryDriver t = *this;
    completedDeliveries++;
    return t;}


string deliveryDriver::getvehicleType(){return vehicleType;}
int deliveryDriver::getcompletedDeliveries(){return completedDeliveries;}
double deliveryDriver::gettotalEarnings(){return totalEarnings;}