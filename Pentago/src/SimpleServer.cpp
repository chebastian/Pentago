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
	shutdownServer();
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
	mConnectSocket = accept(mListenSocket,(SOCKADDR*)&mAddr,&mAddrLen);
	if(mConnectSocket)
	{
		m_vConnections.push_back(mConnectSocket);
		std::cout << "Connection Found" << std::endl;
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
	bool serverRunning = true;

	while(serverRunning)
	{
		std::string msg = std::string("");
		char* cmsg = new char[256];
		ZeroMemory(cmsg,256);

		recv(m_vConnections.at(id),cmsg,256,NULL);
		msg.append(cmsg);
		this->sendMessageToClients(msg);
		delete[] cmsg;
	}
	
	return 0;
}


void SimpleServer::sendMessageToClients(const std::string& msg)
{
	for(unsigned int i = 0; i < m_vConnections.size(); i++)
	{
		send(m_vConnections.at(i),msg.c_str(),msg.length(),NULL);
	}
}

void SimpleServer::sendMessageToClient(const int sender, const int recv, const std::string& msg)
{
	try
	{
		int s = sender;
		s = s;

		SOCKET receiver = getClient(recv);
		send(receiver,msg.c_str(),msg.length(),NULL);
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;

	}
}

SOCKET SimpleServer::getClient(int id)
{
	return m_vConnections.at(id);
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

void SimpleServer::respondToErrorMsg(int error,SOCKET s)
{
	switch(error)
	{
	case WSAEWOULDBLOCK:
		{
		}break;
	case 0:
		{
		}break;
	default:
		{
			shutdown(s,SD_SEND);
		}break;
	}
}

void SimpleServer::shutdownServer()
{
	std::cout << "SHUTING DOWN SOCKETS" << std::endl;
	for(unsigned int i = 0; i < m_vConnections.size(); i++)
	{
		shutdownSocket(m_vConnections.at(i));
	}
	WSACleanup();
}

void SimpleServer::shutdownSocket(SOCKET s)
{
	shutdown(s,SD_SEND);
	closesocket(s);
}
