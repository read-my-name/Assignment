#include <iostream>
#include "include.h"
#include "CMatchTest.h"

int main()
{
    std::cout << "Welcome To Match Engine!\n";
	
	CMatchTest ct1;
	//ct1.vEngineTest();
	CServerChannel cs1;
	cs1.Start([&cs1, &ct1](const std::string& message) {
		cs1.OnMsgReceived(message);
		//std::cout << "Start: " << message << "\n";
		ct1.vEngineStart(message);
		});

	cs1.bServerCreate();

	std::cout << "Main Accept\n";
	cs1.bServerAccept();

	std::cout << "Main Close\n";
	cs1.bServerClose();

	return 0;
}

