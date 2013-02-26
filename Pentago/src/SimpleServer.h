#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include "Runnable.h"

#define NETWORK_ERROR 1
#define NETWORK_OK 0

#define MSG_ONE 0x01
#define MSG_TWO 0x02
#define MSG_THREE 0x03

class SimpleServer : public Runnable
{
public:

	struct Buffer
	{
		int ID;
		char Message[256];
	};

	struct StrBuffer
	{
		std::string ID;
		std::string Message;
	};

	SimpleServer(const std::string& ip);
	~SimpleServer(void);

	int initWinSock();
	int setupSockets();
	
	virtual bool listenForNewConnection();
	int update();
	void sendMessageToClients(const std::string& msg);
	void sendMessageToClient(const int sender, const int recv, const std::string& msg);
	void startServerThread();
	SOCKET getClient(int id);
	virtual void shutdownServer();
	virtual void shutdownSocket(SOCKET s);

	const int numClients() const
	{return m_vConnections.size();}

	bool hasClients()
	{return m_vConnections.size() > 0;}

protected:
	virtual DWORD run();
	virtual void listenToClient(int id);
	SOCKET getLastAddedConnection();

	virtual void respondToErrorMsg(int error, SOCKET s);

	SOCKADDR_IN mAddr;
	SOCKET mListenSocket;
	SOCKET mConnectSocket;
	SOCKET* mConnections;


	int mAddrLen;
	int mConnectionCounter;
	std::string mConnectionIP;
	std::vector<SOCKET> m_vConnections;
};

