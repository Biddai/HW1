#include "../include/Volunteer.h"

// Implementing Volunteer

Volunteer::Volunteer(int id, const string &name) : id(id), name(name),completedOrderId(NO_ORDER),
activeOrderId(NO_ORDER){};

int Volunteer::getId() const{return id;};

const string& Volunteer::getName() const{return name;};

int Volunteer::getActiveOrderId() const{return activeOrderId;};

int Volunteer::getCompletedOrderId() const{return completedOrderId;};

bool Volunteer::isBusy() const{return activeOrderId==NO_ORDER;}; // maybe check completedId too



// Implementing CollectorVolunteer

CollectorVolunteer::CollectorVolunteer(int id, const string &name, int cooldown) : Volunteer(id,name), coolDown(cooldown),timeLeft(0){};

// The caller is responsible for the deletion of the new clone
CollectorVolunteer* CollectorVolunteer::clone() const {
    return new CollectorVolunteer(*this);
}

void CollectorVolunteer::step() {
    if (decreaseCoolDown()){
        completedOrderId=activeOrderId;
        activeOrderId=NO_ORDER; 
    }
};

int CollectorVolunteer::getCoolDown() const {return coolDown;};

int CollectorVolunteer::getTimeLeft() const {return timeLeft;};

// should this method throw an exception if timeLeft==0?
bool CollectorVolunteer::decreaseCoolDown() {
    if (timeLeft>0){--timeLeft;};
    return timeLeft==0;
};

bool CollectorVolunteer::hasOrdersLeft() const {return true;};

// Checks both the volunteer and the order status
bool CollectorVolunteer::canTakeOrder(const Order &order) const {
    return (!isBusy() and order.getStatus()==OrderStatus::PENDING);
};

void CollectorVolunteer::acceptOrder(const Order &order){
    //Reset progress parameters
    timeLeft=coolDown;
    activeOrderId=order.getId();
};

// Again check what kind of string to return
string CollectorVolunteer::toString() const{};



// Implementing LimitedCollectorVolunteer

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, const string &name, int coolDown, int maxOrders):CollectorVolunteer(id,name,coolDown), maxOrders(maxOrders), ordersLeft(maxOrders){};

// The caller is responsible for the deletion of the new clone
LimitedCollectorVolunteer* LimitedCollectorVolunteer::clone() const{
    return new LimitedCollectorVolunteer(*this);
};

bool LimitedCollectorVolunteer::hasOrdersLeft() const{return ordersLeft>0;};

// Also checks ordersLeft
bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const {
    return(hasOrdersLeft() and CollectorVolunteer::canTakeOrder(order));
};

// Should it throw an exception?
void LimitedCollectorVolunteer::acceptOrder(const Order &order) {
    //Reset progress parameters
    CollectorVolunteer::acceptOrder(order);
    //Decrease orders left. When this reaches 0, the warehouse will delete it in stage 4.
    --ordersLeft;
};

// Check what template to use
string LimitedCollectorVolunteer::toString() const{};

