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

		/*if(simpleServer.hasClients())
		{
			std::string msg = std::string("");
			char* cmsg = new char[256];
			std::cin >> cmsg;

			msg.append(cmsg);
			simpleServer.sendMessageToClients(msg);
			delete[] cmsg;
		}*/

	}

	/*int RetVal = 0;
	RetVal = InitWinSock();
	if(RetVal != 0)
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	Connections = (SOCKET*)calloc(64, sizeof(SOCKET));

	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	sConnect = socket(AF_INET, SOCK_STREAM, NULL);

	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port        = htons(1234);
	addr.sin_family      = AF_INET;

	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	
	listen(sListen, 64);

	for(;; Sleep(50))
	{
		if(sConnect = accept(sListen, (SOCKADDR*)&addr, &addrlen))
		{
			Connections[ConCounter] = sConnect;

			char* ID = new char[64];
			ZeroMemory(ID, sizeof(ID));

			itoa(ConCounter, ID, 10);
			send(Connections[ConCounter], ID, sizeof(ID), NULL);

			ConCounter = ConCounter + 1;
			std::cout << "new client connected: " << ID << std::endl;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) itShouldReceiveAndSendMessagesToClient, (LPVOID)(ConCounter - 1), NULL, NULL);
		}
	}
	*/
	return 0;
}