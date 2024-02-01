#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#include "Action.h"

class InputParser{
    public:
        BaseAction* parseUserInput(); // Gets input and calls the correct parser
    private:
        //different parsers for the actions
        BaseAction* parseSimulateStep(istringstream& iss);
        BaseAction* parseAddOrder(istringstream& iss);
        BaseAction* parseAddCustomer(istringstream& iss);
        BaseAction* parsePrintOrderStatus(istringstream& iss);
        BaseAction* parsePrintCustomerStatus(istringstream& iss);
        BaseAction* parsePrintVolunteerStatus(istringstream& iss);
};