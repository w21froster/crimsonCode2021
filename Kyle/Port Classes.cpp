//
//  Port Classes.cpp
//  CrimsonCode
//
//  Created by Kyle Parker on 3/6/21.
//

#include "PortData.hpp"

// MARK: - PortData implimentation:

unordered_map<string, Port> PortData::data = {};


PortData::PortData(string file) {
    try {
        importData(file);
    } catch (PortException& exc) {
        
    }
}

bool PortData::verifyData(string portNumber) {
    try {
        Port port = PortData::data.at(portNumber);
        return verifyData(port);
    } catch (exception& exc) {
        cout << "Port #" << portNumber << " failed verification. Could not locate the key in the map at `PortData::data`!!!\
        nExc Dump: " << exc.what() << "\n\nLine: " << __LINE__ << " - " << __PRETTY_FUNCTION__ << endl << endl;
        return false;
    }
}

bool PortData::verifyData(Port &port) {
    return false;
}

void PortData::importData(string fileName) {
    
}
