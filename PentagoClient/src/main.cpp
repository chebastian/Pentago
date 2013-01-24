#pragma comment(lib, "Ws2_32.lib")
#pragma warning( disable : 4100 )

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include "ClientBase.h"
//#include "SDLWrapper.h"
#include "PentagoBase.h"

using namespace std;


SOCKADDR_IN addr;

SOCKET sConnect;


int main(int *argc, char* argv[])
{
	/*system("cls");

	int RetVal = 0;

	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2,1);
	RetVal = WSAStartup(DllVersion, &wsaData);
	if(RetVal != 0)
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	sConnect = socket(AF_INET, SOCK_STREAM, NULL);

	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port        = htons(1234);
	addr.sin_family      = AF_INET;

	cout << "Connect to Masterserver? [ENTER]" <<endl;
	getchar();
	RetVal = connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));

	if(RetVal != 0)
	{
		MessageBoxA(NULL, "Could not connect to server", "Error", MB_OK | MB_ICONERROR);
		main();
	}
	else
	{
		int ID;
		char* cID = new char[64];
		ZeroMemory(cID, 64);

		recv(sConnect, cID, 64, NULL);

		std::stringstream ss;


		ID = atoi(cID);

		cout << "Connected" <<endl;
		cout << "You are Client No: " << ID <<endl;

        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) ClientThread, NULL, NULL, NULL);
		
		for(;; Sleep(10))
		{
			char* buffer = new char[256];
			ZeroMemory(buffer, 256);

			std::cout << "<" << ID << ">";
			cin >> buffer;
			getchar();
			
			send(sConnect, buffer, 256, NULL);
		}
	}
	*/

	/*ClientBase cBase = ClientBase("127.0.0.1");
	cBase.initWinSock();
	cBase.setupSockets();
	cBase.connectToServer();
	
	SDLWrapper::GetInstance()->Initialize();


	cBase.itShouldReceiveServerMsg();

	while(true)
	{
		SDLWrapper::GetInstance()->Update();

	}*/

	PentagoBase base = PentagoBase();

	base.initGameSystem();
	bool running = true;

	while(running)
	{
		base.render();
		running = base.updateGameSystem();
	}
	
	return 0;
}