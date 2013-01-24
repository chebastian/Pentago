#include "ClientBase.h"


ClientBase::ClientBase(const std::string& ip)
	:Runnable()
{
	mConnectionIP = ip;
	mMessage = "...";
	mThreadRunning = false;
}

ClientBase::~ClientBase(void)
{
}

int ClientBase::initWinSock()
{
	int ok = 0;
	WSAData wsaData;
	WORD Dllverision = MAKEWORD(2,1);
	ok = WSAStartup(Dllverision,&wsaData);
	return ok;
}

int ClientBase::setupSockets()
{
	mConnections = (SOCKET*)calloc(64,sizeof(SOCKET));

	mConnectSocket = socket(AF_INET,SOCK_STREAM,NULL);

	mAddr.sin_addr.s_addr	= inet_addr(mConnectionIP.c_str());
	mAddr.sin_port			= htons(1234);
	mAddr.sin_family		= AF_INET;

	mAddrLen = sizeof(mAddr);

	return RETURN_OK;
}

int ClientBase::connectToServer()
{
	int res = connect(mConnectSocket,(SOCKADDR*)&mAddr,sizeof(mAddr));
	if( res == RETURN_FAIL)
	{
		this->clientShutdown();
		return RETURN_FAIL;
	}

	std::cout << "Connected to server" << std::endl;

	return RETURN_OK;
}

void ClientBase::clientShutdown()
{
	WSACleanup();
	exit(0);
}

DWORD ClientBase::run()
{
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

	}
	return 0;
}

SOCKET ClientBase::itShouldReceiveServerMsg()
{
	mThreadRunning = true;
	CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)Runnable::run_thread,(LPVOID)this,NULL,NULL);
	return NULL;
}

std::string ClientBase::latestMsgFromServer()
{

	return mMessage;
}