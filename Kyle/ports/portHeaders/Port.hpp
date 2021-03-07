//
//  Port.hpp
//  CrimsonCode
//
//  Created by Kyle Parker on 3/7/21.
//

#ifndef Port_h
#define Port_h

class Port {
    unsigned int number;
    
    string serviceName;
    
public:
    Port() {
        this->number = -1;
        this->serviceName = "NO ASSOCIATED SERVICE";
    }
    
    Port(vector<string> vals) {
        this->number = stoi(vals.at(1));
        this->serviceName = vals.at(2);
    }
    
    ~Port() { }
    
    // setters:
    unsigned int setNumber(unsigned int newValue) {
        this->number = newValue;
        return this->number;
    }
    
    string setServiceName(string newValue) {
        this->serviceName = newValue;
        return this->serviceName;
    }
    
    // getters:
    unsigned int getNumber() { return this->number; }
    
    string getServiceName() { return this->serviceName; }
    
    friend std::ostream& operator<< (std::ostream& lhs, const Port& rhs) {
        return lhs << "Port # " << rhs.number << endl << "Service Name: " << rhs.serviceName;
    }
};


#endif /* Port_h */
