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
	portState(const int& newPort, const bool& newState, portState* nextPtr = nullptr, portState* prevPtr = nullptr); // pass by reference to save memory
	bool getState();
	int getPort();
	void setState(bool& newState);
	void setNextPtr(portState* newNextPtr);
	portState* getNextPtr();
	void setPrevPtr(portState* newPrevPtr);
	portState* getPrevPtr();
private:
	int port;
	bool state; // TRUE if open, FALSE if closed
	portState* mpNext;
	portState* mpPrev;
};

class host {
public:
	host(std::string newHostIP = "", portState* pNewHead = nullptr);
	bool testPort(const int& port);
	void printStatus();
private:
	bool newPort(const int& port, const bool& connection_status);
	std::string hostIP;
	portState* mpHead;
};

