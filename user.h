//nadeen mohamed farid 20245070 g6
//yassin nabil mohamed 20245076 g7

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "ENUMS.h"

using namespace std;

class user {

protected :
    string userid ;
    string name ;
    string phonenumber ;
    static int totalusers;

public:

    user();
    user(const string &id , const string &n ,const string &p );


    virtual void displayinfo()const=0;
    virtual double CalculateEarning() const =0;

    static int gettotalusers();


    string getuserid();
    string getname();
    string getphonenumber();


    virtual ~user();

};

#endif
