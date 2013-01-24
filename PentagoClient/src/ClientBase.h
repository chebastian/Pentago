#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

#include "Runnable.h"

#define RETURN_OK 0
#define RETURN_FAIL 1

class ClientBase : public Runnable
{
public:
	ClientBase(const std::string& ip);
	virtual ~ClientBase(void);

	int initWinSock();
	int setupSockets();
	int connectToServer();
	int connectToServer(const std::string& ip);
	void clientShutdown();

	SOCKET itShouldReceiveServerMsg();
	std::string latestMsgFromServer();

protected:
	virtual DWORD run();
	SOCKADDR_IN mAddr;
	SOCKET mListenSocket;
	SOCKET mConnectSocket;
	SOCKET* mConnections;


	int mAddrLen;
	int mConnectionCounter;
	bool mThreadRunning;
	std::string mConnectionIP;
	std::string mMessage;
	std::vector<SOCKET> m_vConnections;
};

