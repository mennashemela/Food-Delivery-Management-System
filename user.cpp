//nadeen mohamed farid 20245070 g6
//yassin nabil mohamed 20245076 g7
#include "user.h"

int user :: totalusers = 0 ;

user::user(){
    userid="";
    name="";
    phonenumber="";
    totalusers++;}


user::user(const string &id,const string &n ,const string &p ){
    userid = id ;
    name = n ;
    phonenumber = p ;
    totalusers ++;}


int user :: gettotalusers(){return totalusers;}


string user::getuserid(){return userid;}
string user::getname(){return name;}
string user::getphonenumber(){return phonenumber;}


user::~user() { totalusers--; }