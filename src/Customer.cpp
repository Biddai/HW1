#include "../include/Customer.h"


Customer::Customer(int id, const string &name, int locationDistance, int maxOrders):id(id),name(name),locationDistance(locationDistance),maxOrders(maxOrders){};

const string &Customer::getName() const{
    return name;
};

int Customer::getId() const{
    return id;
};

int Customer::getMaxOrders() const{
    return maxOrders;
};

int Customer::getNumOrders() const{
   return  ordersId.capacity();
};


bool Customer::canMakeOrder() const{
    return (ordersId.capacity()<maxOrders);
}; 

const vector<int> &Customer::getOrdersIds() const{
   return ordersId;
};
//Need to add validation that the customer can accept the order.
int Customer::addOrder(int orderId){
    ordersId.push_back(orderId);
      return orderId;
};
 // virtual Customer *clone() const = 0; // Return a copy of the customer

SoldierCustomer::SoldierCustomer(int id, string name, int locationDistance, int maxOrders):Customer(id, name,locationDistance,maxOrders){}; 

SoldierCustomer* SoldierCustomer::clone() const{
    return new SoldierCustomer(*this);
};

CivilianCustomer::CivilianCustomer(int id, string name, int locationDistance, int maxOrders):Customer(id,name,locationDistance,maxOrders){};

CivilianCustomer* CivilianCustomer::clone() const{
    return new CivilianCustomer(*this);
};
    
   
 