//
//  loadPortData.hpp
//  CrimsonCode
//
//  Created by Kyle Parker on 3/6/21.
//

// NOTE: 'service-names-port-numbers.csv' downloaded from https://www.iana.org/assignments/service-names-port-numbers/service-names-port-numbers.xhtml

#ifndef PortData_hpp
#define PortData_hpp

#include <iostream> // exception, cout, endl
#include <unordered_map> // unordered_map
#include <string> // string
#include <vector> // vector

using std::unordered_map;
using std::exception;
using std::string;
using std::vector;
using std::cout;
using std::endl;

enum TCPIPProtocol: char {
    TCP = 't',
    UDP = 'u',
    DCCP = 'd',
    SCTP = 's',
    UNKNOWN = 'k'
};

class Port {
public:
    Port() {
        this->number = -1;
        
        this->protocol = UNKNOWN;
        
        this->serviceName = nullptr;
        this->description = nullptr;
        this->refrenceNumber = nullptr;
        this->serviceCode = nullptr;
        this->unauthorizedUse = nullptr;
        this->ianaNotes = nullptr;
        
        this->hasUnauthoriedUse = false;
        this->isOpen = false;
        this->isEmpty = true;
    }
    
    ~Port() {
        
    }
    
    unsigned int number;
    
    TCPIPProtocol protocol;
    
    string serviceName, description, refrenceNumber, serviceCode, unauthorizedUse, ianaNotes;
    
    bool hasUnauthoriedUse;
    bool isOpen;
    bool isEmpty;
};

class PortException: exception {
protected:
    PortException() {description = "Generic Port Exception!"; data = Port();}
    string description;
    Port data;
    long lineNumber;
    string functionName;
};


class PortCreationException: PortException {
public:
    PortCreationException(string description = "Port Creation Exception!") {
        this->data = Port();
        this->description = description;
    }
    
    PortCreationException(Port& data, string description = "Failed to create port object") {
        this->data = data;
        this->description = description;
    }
};

class PortData {
    bool verifyData(string portNumber);
    bool verifyData(Port& port);
    void importData(string fileName);
    
public:
    // (de)constructors:
    
    PortData(string file);
    
    ~PortData();
    
    // static declarations
    static unordered_map<string, Port> data;
};

#endif /* loadPortData_hpp */
