//
//  PortData.hpp
//  CrimsonCode
//
//  Created by Kyle Parker on 3/7/21.
//

#ifndef PortData_h
#define PortData_h

#include "Exceptions.hpp"

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
    
    PortData(const string file)  {
        try {
            importData(file);
        } catch (PortCreationException& exc) {
            cout << "Unexpected error while importing!! Exception Dump:\n" << exc << endl;
            if (exc.getDescription() == "Could not open file!") {
                string resp = "";
                cout << endl << "Enter file name? Yes/No\n> ";
                std::cin >> resp;
                while (!isYes(resp) && !isNo(resp)) {
                    cout << endl << "Invalid Input! Enter file name? Yes/No\n> ";
                    std::cin >> resp;
                }
                
                if (isYes(resp)) {
                    string fileName = "";
                    system(CLEAR_SCREEN_KEY);
                    cout << "Please enter the file name with full path:\n>";
                    cin >> fileName;
                    throw PortCreationException("BadFileNew=" + fileName, __LINE__, __FUNCTION__);
                } else {
                    throw PortCreationException("Bad File, Discard result.", __LINE__, __FUNCTION__);
                }
            }
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
    
    static vector<int> getKeys() {
        vector<int> keys = {};
        
        keys.reserve(PortData::data.size());
        
        for (auto kv: PortData::data) {
            keys.push_back(stoi(kv.first));
        }
        return keys;
    }
    
    // static declarations
    static map<string, Port*> data;
};

#endif /* PortData_h */
