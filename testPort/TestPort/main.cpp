#include "testPort.h"

int main(void) {
	host Test = host::host("127.0.0.1");
	Test.testPort(22);
	Test.testPort(8000);
	Test.testPort(1);
	Test.testPort(75);
	Test.printStatus();
}