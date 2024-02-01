#include "../include/Action.h"

string BaseAction::getStatusAsString() const{
    if(this->getStatus()==ActionStatus::COMPLETED){
        return "COMPLETED";
    }
    else{
        return "ERROR";
    }
};
// Implementing AddOrder

AddOrder::AddOrder(int id):customerId(id){};

//Note - AddOrder does not manage resources.
void AddOrder::act(WareHouse &WareHouse){
    Customer& targetCustomer = WareHouse.getCustomer(this->customerId);
    if (targetCustomer.getId() == -1){ // check if the customer exists
        this->error("Cannot place this order");
    }
    else if(!targetCustomer.canMakeOrder()){ 
        this->error("Cannot place this order");
    }
    else{
        int orderID=WareHouse.getNextOrderId();
        Order* newOrder = new Order(orderID,this->customerId,targetCustomer.getCustomerDistance());
        WareHouse.addOrder(newOrder);
        targetCustomer.addOrder(orderID);
        this->complete();
    }
};

string AddOrder::toString() const {
    return "order "+to_string(customerId)+" "+this->getStatusAsString();
};


AddOrder* AddOrder::clone() const{
    return new AddOrder(*this);
};


//Implementing PrintOrderStatus

PrintOrderStatus::PrintOrderStatus(int id):orderId(id){};

void PrintOrderStatus::act(WareHouse &wareHouse){
    // get the order and check if it exists
    Order order = wareHouse.getOrder(this->orderId);
    if (order.getId()==-1){
        this->error("Order doesn't exist");
    }
    else{
        istringstream iss(order.toString());
        string orderId, orderStatus, customerId, collector,driver;

        // Parse the toString into separate strings
        iss>>orderId>>orderStatus>>customerId>>collector>>driver;
        cout<<"OrderId: "+orderId<<endl;
        cout<<"OrderStatus: "+orderStatus<<endl;
        cout<<"CustomerID: "+customerId<<endl;
        cout<<"Collector: "+collector<<endl;
        cout<<"Driver: "+driver<<endl;
        this->complete();
    }
};

PrintOrderStatus* PrintOrderStatus::clone() const{
    return new PrintOrderStatus(*this);
}

string PrintOrderStatus::toString() const{
    return "orderStatus "+to_string(orderId)+" "+getStatusAsString(); 
};


//Implementing PrintActionsLog

PrintActionsLog::PrintActionsLog(){};

void PrintActionsLog::act(WareHouse &wareHouse){
    vector<BaseAction*> actionsToPrint = wareHouse.getActions();
    for(BaseAction* action : actionsToPrint){
        cout<<action->toString()<<endl;
    };
    this->complete();
};
PrintActionsLog* PrintActionsLog::clone() const{
    return new PrintActionsLog(*this);
};
string PrintActionsLog::toString() const{
    return "log "+getStatusAsString();
};

// Implementing BackupWarehouse
BackupWareHouse::BackupWareHouse(){};

void BackupWareHouse::act(WareHouse &wareHouse){
    if(backup==nullptr){
        backup = new WareHouse(wareHouse);
    }
    else{
        *backup = wareHouse;
    }
    this->complete();
};

BackupWareHouse* BackupWareHouse::clone() const{
    return new BackupWareHouse(*this);
};

string BackupWareHouse::toString() const{
    return "backup "+this->getStatusAsString();
};