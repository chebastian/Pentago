#include "SimpleServer.h"
#include <exception>

SimpleServer::SimpleServer(const std::string& ip)
	:Runnable(), mConnectionIP(ip)
{
	mConnectionCounter = 0;
	m_vConnections = std::vector<SOCKET>();
}


SimpleServer::~SimpleServer(void)
{
}

int SimpleServer::initWinSock()
{
	int ok = 0;
	WSAData wsaData;
	WORD Dllverision = MAKEWORD(2,1);
	ok = WSAStartup(Dllverision,&wsaData);
	return ok;
}

int SimpleServer::setupSockets()
{
	mConnections = (SOCKET*)calloc(64,sizeof(SOCKET));

	mListenSocket = socket(AF_INET,SOCK_STREAM,NULL);
	mConnectSocket = socket(AF_INET,SOCK_STREAM,NULL);

	mAddr.sin_addr.s_addr	= inet_addr(mConnectionIP.c_str());
	mAddr.sin_port			= htons(88);
	mAddr.sin_family		= AF_INET;

	mAddrLen = sizeof(mAddr);
	bind(mListenSocket,(SOCKADDR*)&mAddr,sizeof(mAddr));

	listen(mListenSocket,SOMAXCONN);

	return NETWORK_OK;
}

bool SimpleServer::listenForNewConnection()
{
	if(mConnectSocket = accept(mListenSocket,(SOCKADDR*)&mAddr,&mAddrLen))
	{

		m_vConnections.push_back(mConnectSocket);
		std::cout << "Connection Found" << std::endl;

		//send(getLastAddedConnection(),(char*)id,1,NULL);

		return true;		
	}

	return false;
}

int SimpleServer::update()
{
	return NETWORK_OK;
}

SOCKET SimpleServer::getLastAddedConnection()
{
	SOCKET toGet = NULL;
	try
	{
		toGet = m_vConnections.at(m_vConnections.size()-1);
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return toGet;
}

void SimpleServer::startServerThread()
{
	if(m_vConnections.size() > 1)
	{
		//std::cout << "no new thread created" << std::endl;
	//return;
	}
	CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SimpleServer::run_thread,(LPVOID*)this,NULL,NULL);
}

DWORD SimpleServer::run()
{
	int id = m_vConnections.size()-1;
	while(true)
	{
		std::string msg = std::string("");
		char* cmsg = new char[256];
		ZeroMemory(cmsg,256);

		recv(m_vConnections.at(id),cmsg,256,NULL);
		msg.append(cmsg);
		this->sendMessageToClients(msg);
		delete[] cmsg;
	}
}


void SimpleServer::sendMessageToClients(const std::string& msg)
{
	for(int i = 0; i < m_vConnections.size(); i++)
	{
		send(m_vConnections.at(i),msg.c_str(),msg.length(),NULL);
	}
}

void SimpleServer::listenToClient(int id)
{
	SOCKET s = m_vConnections.at(id);
	const int bufsz = 256;
	char* buff = new char[bufsz];
	ZeroMemory(buff,bufsz);
	recv(s,buff,bufsz,NULL);

	if(s != NULL)
	{
		std::cout << buff << std::endl;
	}

	delete[] buff;
}
