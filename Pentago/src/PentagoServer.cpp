#include "PentagoServer.h"


PentagoServer::PentagoServer(const std::string& ip)
	:SimpleServer(ip)
{
	mThreadSleepTime = 50;
}


PentagoServer::~PentagoServer(void)
{
	
}

bool PentagoServer::listenForNewConnection()
{
	u_long iMode = 1;
	mConnectSocket = accept(mListenSocket,(SOCKADDR*)&mAddr,&mAddrLen);
	if(mConnectSocket)
	{
		ioctlsocket(mConnectSocket,FIONBIO,&iMode);
		m_vConnections.push_back(mConnectSocket);
		std::cout << "Connection Found" << std::endl;

		PentagoClientObj newClient = PentagoClientObj();
		newClient.ID = mConnectedClients.size();

		if(serverHasWaitingClients())
		{
			PentagoClientObj* partner = findUnpairedClient();
			pairupClients(&newClient,partner);
			std::cout << "Clients matched" << std::endl;
		}
		else{
			std::cout << "new client waiting" << std::endl;
		}

		addNewClient(newClient);
		return true;		
	}

	return false;
}

bool PentagoServer::serverHasWaitingClients()
{
	ClientObjects::iterator it = mConnectedClients.begin();
	for(it; it != mConnectedClients.end(); it++)
	{
		if(!(*it).isPaired)
			return true;
	}

	return false;
}

PentagoClientObj* PentagoServer::findUnpairedClient()
{
	ClientObjects::iterator it = mConnectedClients.begin();
	for(it; it != mConnectedClients.end(); it++)
	{
		if(!(*it).isPaired )
		{
			return &(*it);
		}
	}

	return NULL;
}

void PentagoServer::pairupClients(PentagoClientObj* a, PentagoClientObj* b)
{
	a->PartnerID = b->ID;
	b->PartnerID = a->ID;
	a->isPaired = true;
	b->isPaired = true;
}

int PentagoServer::setupSockets()
{
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

DWORD PentagoServer::run()
{
	int id = m_vConnections.size()-1;
	bool threadRunning = true;
	while(threadRunning)
	{
		std::string msg = std::string("");
		char* cmsg = new char[256];
		ZeroMemory(cmsg,256);

		recv(m_vConnections.at(id),cmsg,256,NULL);
		respondToErrorMsg(WSAGetLastError(), getClient(id) );
		
		msg.append(cmsg);

		if(WSAGetLastError() != WSAEWOULDBLOCK)
		{
			if(mConnectedClients.at(id).isPaired)
			{
				int recid = mConnectedClients.at(id).PartnerID;
				this->sendMessageToClient(id,recid,msg);
			}
		}
		delete[] cmsg;

		Sleep(mThreadSleepTime);
	}

	return 0;
}

void PentagoServer::addNewClient(PentagoClientObj client)
{
	mConnectedClients.push_back(client);
}