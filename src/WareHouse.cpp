#include "../include/WareHouse.h"

WareHouse::WareHouse(const string &configFilePath):isOpen(false),customerCounter(1),volunteerCounter(1),
actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(),
defaultCustomer(new SoldierCustomer(-1,"Default",0,0)),defaultVolunteer(new CollectorVolunteer(-1,"Default",0)),
defaultOrder(new Order(-1,-1,0)){
    ParsedFile input = parseFile(configFilePath);
    addInputCustomers(input.customers);
    addInputVolunteers(input.volunteers);
};

void WareHouse::addInputCustomers(vector<CustomerInput> customerInput){
    for(CustomerInput customer : customerInput){
        if(customer.role=="soldier"){
            this->customers.push_back(new SoldierCustomer(customerCounter,customer.name,customer.distance,customer.maxOrders));
        }
        else{
            this->customers.push_back(new CivilianCustomer(customerCounter,customer.name,customer.distance,customer.maxOrders));
        }
        ++customerCounter;
    }
};

void WareHouse::addInputVolunteers(vector<VolunteerInput> volunteerInput){
    
    for(VolunteerInput volunteer : volunteerInput){
        Volunteer* currentVolunteer;

        if(volunteer.role=="collector"){
            currentVolunteer = &CollectorVolunteer(volunteerCounter, volunteer.name,volunteer.coolDownOrMaximumDistance);
        }
        else if(volunteer.role=="limited_collector"){
            currentVolunteer = &LimitedCollectorVolunteer(volunteerCounter, volunteer.name,volunteer.coolDownOrMaximumDistance,volunteer.maxOrders);
        } 
        else if(volunteer.role=="driver"){
            currentVolunteer = &DriverVolunteer(volunteerCounter,volunteer.name,volunteer.coolDownOrMaximumDistance,volunteer.distancePerStep);
        }
        else if(volunteer.role=="limited_driver"){
            currentVolunteer = &LimitedDriverVolunteer(volunteerCounter,volunteer.name,volunteer.coolDownOrMaximumDistance,volunteer.distancePerStep,volunteer.maxOrders);
        }
        // Validation not needed (?)
        else{
            cout<< "Invalid volunteer role"<<endl;
        }
        this->volunteers.push_back(currentVolunteer);
        ++volunteerCounter;
    }

};
// 
void WareHouse::addOrder(Order* order){
    this->pendingOrders.push_back(order);
    this->orderCounter+=1;
};

int WareHouse::getNextOrderId() const{
    return this->orderCounter;
};

void WareHouse::addAction(BaseAction* action){
    this->actionsLog.push_back(action);

};

Customer& WareHouse::getCustomer(int customerId) const{
    if(isCustomerAlive(customerId)){
        for(Customer* customer : customers){
            if ((customer)->getId()==customerId){
                return *customer;}
        }
    }
    return *defaultCustomer;
};

bool WareHouse::isCustomerAlive(int customerId) const{
    return ((this->customerCounter)>=customerId);
};

Volunteer& WareHouse::getVolunteer(int volunteerId) const{ 
    for(Volunteer* volunteer : volunteers){
        if ((volunteer)->getId()==volunteerId){
            return *volunteer;}
    }
    return *defaultVolunteer;
};

Order& WareHouse::getOrder(int orderId) const{
    for(Order* order : pendingOrders){
        if ((order)->getId() == orderId){
            return *order;
        }
    }
        for(Order* order : inProcessOrders){
        if ((order)->getId() == orderId){
            return *order;
        }
    }
        for(Order* order : completedOrders){
        if ((order)->getId() == orderId){
            return *order;
        }
    }
    return *defaultOrder;
};

bool WareHouse::isOrderAlive(int orderId) const{
    return (orderId<=orderCounter);
};

const vector<BaseAction*>& WareHouse::getActions() const{
    return actionsLog;
};

// Unsure how to implement yet
void WareHouse::start(){
    this->open();
    while(this->isOpen){// loop for user input
        cout << "Enter an action: " << endl;
        // Read user input
        string userInput;
        getline(cin, userInput);
        
        //Parse the action
        istringstream iss(userInput);
        string action;
        
    }
};

void WareHouse::close(){
    // Print all the orders
    for(BaseAction* action : actionsLog){
        cout<<action->toString()<<endl;
    }
    //Free up memory
    delete this;
};


void WareHouse::open(){
    // Change status of the warehouse
    isOpen = true;
    cout << "Warehouse is open!" <<endl;
};


// Implementing the rule of 5
// Destructor
WareHouse::~WareHouse(){
    // Destroy the default objects
    freeUpDefaults();
    //Destroy pointers from the vectors
    freeUpVectors();
}

//copy constructor
WareHouse::WareHouse(const WareHouse &other):isOpen(other.isOpen),customerCounter(other.customerCounter),
volunteerCounter(other.volunteerCounter),orderCounter(other.orderCounter),actionsLog(), volunteers(), pendingOrders(), inProcessOrders(), completedOrders(), customers(),
defaultCustomer(new SoldierCustomer(-1,"Default",0,0)),defaultVolunteer(new CollectorVolunteer(-1,"Default",0)),
defaultOrder(new Order(-1,-1,0)){
    //Copy the vectors one by one
    this->copyVectors(other);
};

// Copy assignment operator
WareHouse& WareHouse::operator=(const WareHouse& other){
    if(this != &other){
        freeUpVectors();
        // Copy counters
        this->customerCounter=other.customerCounter;
        this->volunteerCounter=other.volunteerCounter;
        this->orderCounter=other.orderCounter;
    }
    return *this;
};

// Move copy constructor
WareHouse::WareHouse(WareHouse&& other):
isOpen(move(other.isOpen)),
customerCounter(other.customerCounter),
volunteerCounter(other.volunteerCounter),
orderCounter(other.orderCounter),
actionsLog(move(other.actionsLog)),
volunteers(move(other.volunteers)),
pendingOrders(move(other.pendingOrders)),
inProcessOrders(move(other.inProcessOrders)),
completedOrders(move(other.completedOrders)),
customers(move(other.customers)),
defaultCustomer(other.defaultCustomer),
defaultVolunteer(other.defaultVolunteer),
defaultOrder(other.defaultOrder)
{
    other.defaultCustomer = nullptr;
    other.defaultVolunteer = nullptr;
    other.defaultOrder = nullptr;
};

// Move Assignment Operator
WareHouse& WareHouse::operator=(WareHouse&& other){
    if(this != &other){
        //Free up resources in this
        this->freeUpVectors();
        this->freeUpDefaults();
        //Move resources from other to this
        isOpen = move(other.isOpen);
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        orderCounter = other.orderCounter;
        actionsLog = move(other.actionsLog);
        volunteers = move(other.volunteers);
        pendingOrders = move(other.pendingOrders);
        inProcessOrders = move(other.inProcessOrders);
        completedOrders = move(other.completedOrders);
        customers = move(other.customers);
        defaultCustomer = other.defaultCustomer;
        defaultVolunteer = other.defaultVolunteer;
        defaultOrder = other.defaultOrder;
        // Nullify pointers from other
        other.defaultCustomer = nullptr;
        other.defaultVolunteer = nullptr;
        other.defaultOrder = nullptr;
    }
    return *this;
};

void WareHouse::freeUpVectors(){
    for(Order* order:pendingOrders){
        delete order;
    }
    for(Order* order:inProcessOrders){
        delete order;
    }
    for(Order* order:completedOrders){
        delete order;
    }
    for(Customer* customer : customers){
        delete customer;
    }
    for(BaseAction* action : actionsLog){
        delete action;
    }
    for(Volunteer* volunteer : volunteers){
        delete volunteer;
    }
};

void WareHouse::freeUpDefaults(){
        delete this->defaultCustomer;
        delete this->defaultVolunteer;
        delete this->defaultOrder;
};

void WareHouse::copyVectors(const WareHouse& other){
    for(BaseAction* action : other.actionsLog){
        this->actionsLog.push_back(action->clone());
    }
    for(Volunteer* volunteer : other.volunteers){
        this->volunteers.push_back(volunteer->clone());
    }
    for(Order* order : pendingOrders){
        this->pendingOrders.push_back(order->clone());
    }
    for(Order* order : inProcessOrders){
        this->pendingOrders.push_back(order->clone());
    }
    for(Order* order : completedOrders){
        this->pendingOrders.push_back(order->clone());
    }
    for(Customer* customer : other.customers){
        this->customers.push_back(customer->clone());
    }
};