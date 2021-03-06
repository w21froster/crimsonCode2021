//
//  loadPortData.hpp
//  CrimsonCode
//
//  Created by Kyle Parker on 3/6/21.
//

// NOTE: 'service-names-port-numbers.csv' downloaded from https://www.iana.org/assignments/service-names-port-numbers/service-names-port-numbers.xhtml

#ifndef PortData_hpp
#define PortData_hpp

#include <iostream>
#include <unordered_map>

using std::unordered_map;
using std::string;

class Port {
public:
    enum protocol: char {
        TCP = 't',
        UDP = 'u',
        DCCP = 'd',
        SCTP = 's',
        UNKNOWN = 'k'
    };
    
    string serviceName;
    
};

class PortData {
    
    
public:
    static unordered_map<string, int> data;
    
    void importData(string fileName, bool isFilePath);
    
    
};



#endif /* loadPortData_hpp */
