#include "../include/Parser.h"

void parseCustomer(const string& line, vector<CustomerInput>& customers){
    istringstream iss(line);
    string type, name, role;
    int distance, maxOrders;
    
    iss >> type >> name >> role >> distance >> maxOrders;

    // Construct using the default constructor, note the order!
    if (type=="customer"){
        customers.push_back({name,role,distance,maxOrders});
    }

}

void parseVolunteer(const string& line, vector<VolunteerInput>& volunteers){
    istringstream iss(line);
    string type, name, role;
    int coolDownOrMaximumDistance, distancePerStep, maxOrders;

    iss >> type >> name >> role >> coolDownOrMaximumDistance;

    if(role=="driver" or role=="limited_driver"){
        iss >> distancePerStep >> maxOrders;
        cout <<distancePerStep <<endl;
        cout << maxOrders << endl;
    }
    else{
        iss >> maxOrders;
        distancePerStep = 0;
    }
    // Construct using the default constructor, note the order!
    if (type=="volunteer"){
        volunteers.push_back({name,role,coolDownOrMaximumDistance, distancePerStep, maxOrders});
    }
}

ParsedFile parseFile(const string& fileLocation){
    ifstream inputFile(fileLocation);

    if(!inputFile.is_open()){
        cerr << "Error opening file" << endl;
        return ParsedFile{};
    }

    // Initialize the input vectors

    vector<CustomerInput> customers;
    vector<VolunteerInput> volunteers;
    string line;

    while(getline(inputFile,line)){
        if(line.empty() or line[0] == '#'){
            continue;
        }
        if(line.find("customer") != string::npos){
            parseCustomer(line, customers);
        }
        else if (line.find("volunteer") != string::npos){
            parseVolunteer(line, volunteers);
        }
    }
    return ParsedFile{customers,volunteers};
}  
