#include "ChatClient.h"


ChatClient::ChatClient(const std::string& ip)
	:ClientBase(ip)
{
	mConnected = false;
	mMessages = std::vector<std::string>();
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
	const int RETRY_INTERVAL = 200;

	while(!mConnected || counter >= MAX_RETRYS)
	{
		std::cout << "Client: Waiting for server response..." << std::endl;		
		int res = connect(mConnectSocket,(SOCKADDR*)&mAddr,sizeof(mAddr));
		if( res == RETURN_OK)
		{
			u_long iMode = 1;
			ioctlsocket(mConnectSocket,FIONBIO,&iMode);
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

		int err = WSAGetLastError();
		if(err != WSAEWOULDBLOCK && err != 0)
		{
			delete[] buffer;
			clientShutdown();
			return 1;
		}

		if(WSAGetLastError() == WSAEWOULDBLOCK)
		{
			delete[] buffer;
			continue;
		}


		std::cout << "bytes:  " << i << std::endl;
		std::cout << buffer << std::endl;
		mMessage = std::string(buffer);
		//mMessages.push_back(mMessage);
		delete[] buffer;
		Sleep(RETRY_INTERVAL);

		//send message to server

	}
	return 0;
}	

bool ChatClient::newMessageRcvdFromServer()
{
	return false;
}

ChatClient::Messages ChatClient::getMessages()
{
	return mMessages;
}