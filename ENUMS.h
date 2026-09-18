//nadeen mohamed farid 20245070 g6
//yassin nabil mohamed 20245076 g7


#ifndef ENUMS_H
#define ENUMS_H

#include <string>

using namespace std;

enum class OrderStatus { PENDING, PREPARING, OUT_FOR_DELIVERY, DELIVERED, CANCELLED };
enum class UserType { CUSTOMER , DRIVER };

std::string orderStatusToString(OrderStatus status);

#endif