#include "../include/InputParser.h"

BaseAction* InputParser::parseUserInput(){
        cout << "Enter an action: " << endl;
        // Read user input
        string userInput;
        getline(cin, userInput);
        
        //Parse the action
        istringstream iss(userInput);
        string action;
        BaseAction* output;
        iss>>action;
        if(action=="step"){
            output=parseSimulateStep(iss);
        }
        else if(action=="order"){
            output = parseAddOrder(iss);
        }
        else if(action=="customer"){
            output = parseAddCustomer(iss);
        }
        else if(action=="orderStatus"){
            output = parsePrintOrderStatus(iss);
        }
        else if(action=="volunteerStatus"){
            output = parsePrintVolunteerStatus(iss);
        }
        else if(action=="log"){
            output = new PrintActionsLog();
        }
        else if(action=="close"){
            output = new Close();
        }
        else if(action=="backup"){
            output = new BackupWareHouse();
        }
        else if(action=="restore"){
            output = new RestoreWareHouse();
        }
        else{
            cout<< "That is not a legal action" <<endl;
        }
        return output;
};

BaseAction* parseSimulateStep(istringstream& iss){
    int numOfSteps;
    iss>>numOfSteps;
    return (new SimulateStep(numOfSteps));
};

BaseAction* parseAddOrder(istringstream& iss){
    int orderId;
    iss>>orderId;
    return (new AddOrder(orderId));
};

BaseAction* parseCustomer(istringstream& iss){
    string name, type;
    int distance, maxOrders;

    iss>>name>>type>>distance>>maxOrders;
    return (new AddCustomer(name,type,distance,maxOrders));
};

BaseAction* parsePrintOrderStatus(istringstream& iss){
    int orderId;
    iss>>orderId;
    return (new PrintOrderStatus(orderId));
};

BaseAction* parsePrintCustomerStatus(istringstream& iss){
    int customerId;
    iss>>customerId;
    return (new PrintCustomerStatus(customerId));
};
BaseAction* parsePrintVolunteerStatus(istringstream& iss){
    int volunteerId;
    iss>>volunteerId;
    return (new PrintVolunteerStatus(volunteerId));
};
