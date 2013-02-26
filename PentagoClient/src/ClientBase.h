#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "SFMessage.h"
#include "Runnable.h"
#include "Vector2D.h"

#include "ClientMessage.h"

#define RETURN_OK 0
#define RETURN_FAIL -1

class ClientBase : public Runnable
{
public:
	ClientBase(const std::string& ip);
	virtual ~ClientBase(void);

	int initWinSock();
	int setupSockets(bool blocking);
	virtual int connectToServer();
	int connectToServer(const std::string& ip);
	void clientShutdown();

	SOCKET itShouldReceiveServerMsg();
	std::string latestMsgFromServer();
	void SendMessageToServer(const std::string& msg);

	int getClientID()
	{
		return mClientID;
	}

	bool ConnectedToServer()
	{return mConnected;}

protected:

	virtual DWORD run();
	bool waitTillFinishedRecv();
	SOCKADDR_IN mAddr;
	SOCKET mListenSocket;
	SOCKET mConnectSocket;
	SOCKET* mConnections;

	bool mConnected;
	int mClientID;
	int mAddrLen;
	int mConnectionCounter;
	bool mThreadRunning;
	std::string mConnectionIP;
	std::string mMessage;
	std::vector<SOCKET> m_vConnections;
};

