#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


struct CustomerInput{
        string name;
        string role;
        int distance;
        int maxOrders;
};

struct VolunteerInput{
    string name;
    string role;
    int coolDownOrMaximumDistance;
    int distancePerStep;
    int maxOrders;
};
// struct for returning the parsed file 
struct ParsedFile{
    vector<CustomerInput> customers;
    vector<VolunteerInput> volunteers;
};


void parseCustomer(const string& line, vector<CustomerInput>& customers);

void parseVolunteer(const string& line, vector<VolunteerInput>& volunteers);

ParsedFile parseFile(const string& fileLocation);

