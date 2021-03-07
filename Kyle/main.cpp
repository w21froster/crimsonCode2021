//
//  main.cpp
//  CrimsonCode
//
//  Created by Kyle Parker on 3/6/21.
//

#include "ports/PortSystem.hpp"
#include "testPort.h"

int main(int argc, const char* argv[]) {
    std::string hostIP,
    customPortDescription = "User chosen port";
    int choice = 0,
    customPort = 0;
    while (1) {
        system(CLEAR_SCREEN_KEY);
        std::cout << "Welcome to the IPv4 / IPv6 TCP port scanner!" << std::endl;
        std::cout << "Please enter a host IP address to get started: " << std::endl;
        std::cin >> hostIP;
        std::cout << "1) Scan a specific port" << std::endl;
        std::cout << "2) Scan well-known ports" << std::endl;
        std::cout << "3) Exit the program" << std::endl;
        std::cin >> choice;
        switch (choice) {
        case 1:
            {
                std::cout << "Please enter a TCP port number: " << std::endl;
                std::cin >> customPort;
                host testHost = host::host(hostIP);
                testHost.testPort(customPort, customPortDescription);
                system("pause");
                break;
            }
        case 2:
            {
                int currentPort = 0;
                std::string currentDescription = "";
                string fileName = "ports/supportingFiles/ports.csv";
                while (true) {
                    try {
                        PortData(fileName);
                        break;
                    } catch (PortCreationException& exc) {
                        if (exc.getDescription().find("BadFileNew=") != string::npos) {
                            fileName = exc.getDescription().substr(exc.getDescription().find("=") + 1);
                        }
                    }
                }
                host testHost = host::host(hostIP);
                vector<int> portList = PortData::getKeys();
                std::sort(portList.begin(), portList.end());
                for (int port : portList) {
                    currentPort = port;
                    currentDescription = PortData::data.find(std::to_string(port))->second->getServiceName();
                    testHost.testPort(currentPort, currentDescription);
                }
                system("pause");
                break;
            }
        case 3:
            {
                std::cout << "Thanks for checking out our program!" << std::endl;
                std::cout << "Credits: Kyle Parker, Zakiya Pruitt, William Foster " << std::endl;
                system("pause");
                return 0;
            }
        default:
            {
                std::cout << "You have entered an invalid selection!" << std::endl;
                system("pause");
            }
        }
    }
    
    return 0;
}
