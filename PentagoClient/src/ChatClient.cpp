#include "ChatClient.h"


ChatClient::ChatClient(const std::string& ip)
	:ClientBase(ip)
{
	mConnected = false;
}


ChatClient::~ChatClient(void)
{
}

int ChatClient::connectToServer()
{
	CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ChatClient::run_thread,(LPVOID)this,NULL,NULL);
	return RETURN_OK;
}
DWORD ChatClient::run()
{
	int counter = 0;
	mThreadRunning = true;
	const int MAX_RETRYS = 20;
	const int RETRY_INTERVAL = 500;
	while(!mConnected || counter >= MAX_RETRYS)
	{
		std::cout << "Client: Waiting for server response..." << std::endl;
		int res = connect(mConnectSocket,(SOCKADDR*)&mAddr,sizeof(mAddr));
		if( res == RETURN_OK)
		{
			mConnected = true;
			std::cout << "Server: OK" << std::endl;
			break;
		}
		std::cout << "Client: No response, Retrying in " << RETRY_INTERVAL << "ms" << std::endl;
		Sleep(RETRY_INTERVAL);
		counter++;
	}

	if(!mConnected)
	{
		std::cout << "Client cannot reach server, timeout" << std::endl;
		clientShutdown();
	}

	while(mThreadRunning)
	{
		const int bufsz = 64;
		char* buffer = new char[bufsz];
		int i = 0;
		ZeroMemory(buffer, bufsz);
		i = recv(mConnectSocket,buffer,bufsz,NULL);

		if(i <= 0)
		{
			delete[] buffer;
			clientShutdown();
			return 1;
		}

		std::cout << "bytes:  " << i << std::endl;
		std::cout << buffer << std::endl;
		mMessage = std::string(buffer);

		delete[] buffer;

		//send message to server

	}
	return 0;
}	

bool ChatClient::newMessageRcvdFromServer()
{
	return false;
}