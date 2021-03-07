//
//  Exceptions.hpp
//  CrimsonCode
//
//  Created by Kyle Parker on 3/7/21.
//

#ifndef Exceptions_h
#define Exceptions_h

#include "ExternLibs.hpp"
#include "Port.hpp"

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
    
    string getDescription() {
        return this->description;
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

#endif /* Exceptions_h */
