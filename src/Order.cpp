#include "../include/Order.h"

Order::Order(int id, int customerId, int distance): id(id), customerId(customerId), distance(distance), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER), status(OrderStatus::PENDING){};

int Order::getId() const{return id;};

int Order::getCustomerId() const {return customerId;};

void Order::setStatus(OrderStatus status){status=status;};

void Order::setCollectorId(int collectorId){
    collectorId = collectorId;
    setStatus(OrderStatus::COLLECTING);
};

void Order::setDriverId(int driverId){
    driverId=driverId;
    setStatus(OrderStatus::DELIVERING);
};

int Order::getCollectorId() const{return collectorId;};

int Order::getDriverId() const{return driverId;};

OrderStatus Order::getStatus() const{return status;};


const string Order::toString() const{
    //Set None to specific strings
    string orderId = to_string(this->id);
    string orderStatus = this->getStatusAsString();
    string customerId = to_string(this->customerId);
    string collector,driver;
    if(this->collectorId == NO_VOLUNTEER){
        collector = "None";
    }
    else{
        collector = to_string(this->collectorId);
    }
    if(this->driverId == NO_VOLUNTEER){
        driver = "None";
    }
    else{
        driver = to_string(this->driverId);
    }
    return orderId+" "+orderStatus+" "+customerId+" "+collector+" "+driver;
};

string Order::getStatusAsString() const{

    if(this->status == OrderStatus::PENDING){
        return "Pending";
    }
    else if (this->status == OrderStatus::COLLECTING){
        return "Collecting";
    }
    else if(this->status == OrderStatus::DELIVERING){
        return "Delivering";
    }
    else{
        return "Completed";
    }

};

int Order::getDistance() const{return distance;};

Order* Order::clone() const{
    return new Order(*this);
};
