#pragma once
#include <string>
#include <vector>
using namespace std;

#include "Order.h"
#include "Customer.h"
#include "Parser.h"
#include "Volunteer.h"

class BaseAction;
class Volunteer;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.

class WareHouse {

    public:
        //rule of 5
        WareHouse(const WareHouse &other);
        ~WareHouse();
        WareHouse& operator=(const WareHouse& other);
        WareHouse(WareHouse&& other);
        WareHouse& operator=(WareHouse&& other);

        // Default methods 
        WareHouse(const string &configFilePath);
        void start();
        void addOrder(Order* order);
        void addAction(BaseAction* action);
        Customer &getCustomer(int customerId) const; //If no customer exists, we return a default customer with ID=-1
        Volunteer &getVolunteer(int volunteerId) const;//If no volunteer exists, we return a default volunteer with ID=-1
        Order &getOrder(int orderId) const;
        const vector<BaseAction*> &getActions() const;
        void close();
        void open();

        // custom methods
        bool isCustomerAlive(int customerId) const;
        bool isOrderAlive(int orderId) const;
        int getNextOrderId() const;

    private:
        bool isOpen;
        Customer* defaultCustomer;
        Volunteer* defaultVolunteer;
        Order* defaultOrder;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders; 
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        // Additional methods and variables
        int orderCounter; // For assigning unique order IDs
        //Methods that call the config parser
        void addInputCustomers(vector<CustomerInput> customerInput);
        void addInputVolunteers(vector<VolunteerInput> volunteerInput);
        
        //Supplementary methods for rule of 5
        void freeUpVectors();
        void freeUpDefaults();
        void copyVectors(const WareHouse& other);
};  