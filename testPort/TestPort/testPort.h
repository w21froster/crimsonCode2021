#pragma once

#define ASIO_STANDALONE

#include <boost/asio.hpp>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

using namespace boost;

// linked lists of portStates with head inside of host
class portState {
public:
	portState(const int& newPort, const bool& newState, std::string& newDescription, portState* nextPtr = nullptr, portState* prevPtr = nullptr); // pass by reference to save memory
	std::string getState();
	int getPort();
	void setState(bool& newState);
	void setNextPtr(portState* newNextPtr);
	portState* getNextPtr();
	void setPrevPtr(portState* newPrevPtr);
	portState* getPrevPtr();
	void setDescription(std::string& newDescription);
	std::string getDescription();

private:
	int port;
	bool state; // TRUE if open, FALSE if closed
	std::string description;
	portState* mpNext;
	portState* mpPrev;
};

class host {
public:
	host(std::string newHostIP = "", portState* pNewHead = nullptr);
	bool testPort(const int& port, std::string& description);
	void printStatus();
private:
	bool newPort(const int& port, const bool& connection_status, std::string& description);
	std::string hostIP;
	portState* mpHead;
};

