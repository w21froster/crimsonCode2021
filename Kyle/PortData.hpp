//
//  loadPortData.hpp
//  CrimsonCode
//
//  Created by Kyle Parker on 3/6/21.
//

// NOTE: 'ports.csv' came from https://github.com/maraisr/ports-list/blob/master/all.csv

#ifndef PortData_hpp
#define PortData_hpp

#include <iostream> // std::exception, std::cout, std::endl
#include <unordered_map> // std::unordered_map
#include <string> // std::string, std::stoi, std::to_string
#include <vector> // std::vector
#include <fstream> // std::ios::in

using std::unordered_map;
using std::exception;
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::fstream;
using std::ios;
using std::stoi;
using std::to_string;

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
    PortCreationException(string description, long lineNumber, string functionName) {
        this->data = Port();
        this->description = description;
        this->lineNumber = lineNumber;
        this->functionName = functionName;
    }
    
    friend std::ostream& operator<< (std::ostream& lhs, const PortCreationException& rhs) {
        return lhs << "---BEGIN EXCEPTION DUMP---\nLine Number  -  function: " << rhs.lineNumber << "  -  " << rhs.functionName << "Description: " << rhs.description << endl << rhs.data << endl << "---END EXCEPTION DUMP---" << endl;
    }
};

class PortVerifcationException: PortException {
public:
    PortVerifcationException(Port& data, string description, long lineNumber, string functionName) {
        this->data = data;
        this->description = description;
        this->lineNumber = lineNumber;
        this->functionName = functionName;
    }
    
    friend std::ostream& operator<< (std::ostream& lhs, const PortVerifcationException& rhs) {
        return lhs << "---BEGIN EXCEPTION DUMP---\nLine Number  -  function: " << rhs.lineNumber << "  -  " << rhs.functionName << "Description: " << rhs.description << endl << rhs.data << endl << "---END EXCEPTION DUMP---" << endl;
    }
};

class PortData {
    bool verifyData(string portNumber) {
        try {
            Port port = *PortData::data.at(portNumber);
            return verifyData(port);
        } catch (exception& exc) {
            cout << "Port #" << portNumber << " failed verification. Could not locate the key in the map at `PortData::data`!!!\
            nExc Dump: " << exc.what() << "\n\nLine: " << __LINE__ << " - " << __PRETTY_FUNCTION__ << endl << endl;
            return false;
        }
    }
    
    bool verifyData(Port& port) {
        if (port.getNumber() == (unsigned int)-1) {
            throw PortVerifcationException(port, "Invalid number detected! Value must not be -1!", __LINE__, __PRETTY_FUNCTION__);
        } else if (port.getServiceName() == "") {
            throw PortVerifcationException(port, "Invalid service name detected! Value must not be ''!", __LINE__, __PRETTY_FUNCTION__);
        }
        return true;
    }
    
    void importData(const string fileName) {
        fstream file;
        file.open(fileName, ios::in);
        
        string line;
        
        if (!file.is_open()) {
            throw PortCreationException("Could not open file!", __LINE__, __PRETTY_FUNCTION__);
        }
        
        while (getline(file, line)) {
            if (line.find("protocol") != string::npos && line.find("port") != string::npos && line.find("description") != string::npos) { continue; }
            
            vector<string> parts = {};
            
            for (int i = 0; i < 3; i += 1) {
                parts.push_back(line.substr(0,line.find(",")));
                try {
                    line = line.substr(line.find(",") + 1);
                } catch (exception& exc) {
                    cout << "i = " << i << "line: " << __LINE__ << endl << exc.what() << endl;
                    line = "";
                    break;
                }
            }
            
            string ports = parts.at(1);
            
            string dataPt = parts.at(1);
            PortData::data[dataPt] = new Port(parts);
        }
        
        file.close();
    }
    
public:
    // (de)constructors:
    
    PortData(const string file)  {
        try {
            importData(file);
        } catch (PortCreationException& exc) {
            cout << "Unexpected error while importing!! Exception Dump:\n" << exc << endl;
        }
    }
    
    ~PortData() { }
    
    string getDescription(string port) {
        if (PortData::data.find(port) == PortData::data.end()) {
            return "DNE";
        } else {
            return PortData::data.find(port)->second->getServiceName();
        }
    }
    
    // static declarations
    static unordered_map<string, Port*> data;
};

#endif /* loadPortData_hpp */
