//Multithreaded = Able to run on other pc`s
//

#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include "SimpleServer.h"
#include "PentagoServer.h"

using namespace std;

// Ok at first I am going to do some WinSock standard stuff
// If you don`t understand it watch my other tutorials

int main()
{
	PentagoServer simpleServer = PentagoServer("127.0.0.1");
	simpleServer.initWinSock();
	simpleServer.setupSockets();
	bool appRunning = true;

	while(appRunning)
	{
		if(simpleServer.listenForNewConnection())
		{
			std::cout << "Waiting..." << std::endl;

			if(simpleServer.hasClients())
			{
				std::cout << "Starting first thread" << std::endl;
				simpleServer.startServerThread();
			}
		}
	}
	return 0;
}