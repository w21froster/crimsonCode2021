/*
* Author: William Foster
* Date: 03/06/2021
* Version:
* Description:
*/


#include "testPort.h"

// port state functions
portState::portState(const int& newPort, const bool& newState, std::string& newDescription, portState* nextPtr, portState* prevPtr) {
	this->state = newState;
	this->port = newPort;
	this->mpNext = nextPtr;
	this->mpPrev = prevPtr;
	this->description = newDescription;
}

std::string portState::getState() {
	std::string open = "OPEN";
	std::string closed = "CLOSED";
	if (this->state) {
		return open;
	}
	else {
		return closed;
	}
};

void portState::setState(bool& newState) {
	this->state = newState;
}

int portState::getPort() {
	return this->port;
}

void portState::setPrevPtr(portState* newPrevPtr) {
	this->mpPrev = newPrevPtr;
}

portState* portState::getPrevPtr() {
	return this->mpPrev;
}

void portState::setNextPtr(portState* newNextPtr) {
	this->mpNext = newNextPtr;
}

portState* portState::getNextPtr() {
	return this->mpNext;
}

void portState::setDescription(std::string& newDescription) {
	this->description = newDescription;
}

std::string portState::getDescription() {
	return this->description;
}
// host functions
host::host(std::string newHostIP, portState* pNewHead) {
	this->mpHead = pNewHead;
	this->hostIP = newHostIP;
}

bool host::newPort(const int& port, const bool& connection_status, std::string& description) {
	bool allocation_success = false;
	portState* pPrev = nullptr;

	// create copy of pointer to iterate through
	portState* pTemp = this->mpHead;
	// create node to store status
	portState* pMem = nullptr;
	pMem = new portState(port, connection_status, description);

	if (pMem != nullptr) {
		allocation_success = true;

		//empty list?
		if (this->mpHead == nullptr) {
			this->mpHead = pMem;
		}
		else { // add to list in numerical order
			while (pTemp != nullptr && pTemp->getPort() < port) { // short circuit evaluation
				pPrev = pTemp;
				pTemp = pTemp->getNextPtr();
			}
			// did we not find a greater value and just make it to the end of the list?
			if (pTemp == nullptr) {
				pPrev->setNextPtr(pMem);
				pMem->setPrevPtr(pPrev);
			}
			// are we at the front of the list?
			else if (this->mpHead == pTemp) {
				pMem->setNextPtr(this->mpHead);
				this->mpHead->setPrevPtr(pMem);
				this->mpHead = pMem;
			}
			// otherwise we are in the middle of the list
			else {
				pPrev = pTemp->getPrevPtr();

				// insert into list
				pPrev->setNextPtr(pMem);
				pMem->setPrevPtr(pPrev);
				pMem->setNextPtr(pTemp);
				pTemp->setPrevPtr(pMem);
			}
		}
		std::cout << "Port: " << pMem->getPort() << " State: " << pMem->getState() << " Description: " << pMem->getDescription() << std::endl;
	}

	return allocation_success;
}

bool host::testPort(const int& port, std::string& description) {
	bool connection_status = false;
	// convert raw string to IP address (can be v4 or v6)
	asio::ip::address targetIP = asio::ip::address::from_string(hostIP);

	// create endpoint from IP address and port
	asio::ip::tcp::endpoint targetServer(targetIP, port);
	
	asio::io_service iosObject;

	// open a socket
	asio::ip::tcp::socket socketObject(iosObject, targetServer.protocol());
	try {
		socketObject.connect(targetServer);
		// did we open a socket?
		if (socketObject.is_open() == true) {
			connection_status = true;
		}
	}
	catch (std::system_error& e) {
		//std::cout << "Error occured! Error code = " << e.code()
		//	<< ". Message: " << e.what();
		connection_status = false;
	}

	
	// save in doubly linked list
	newPort(port, connection_status, description);
	return connection_status;
}

void host::printStatus() {
	portState* pTemp = this->mpHead;
	while (pTemp != nullptr) {
		std::cout << "Port: " << pTemp->getPort() << " State: " << pTemp->getState() << std::endl;
		pTemp = pTemp->getNextPtr();
	}
}