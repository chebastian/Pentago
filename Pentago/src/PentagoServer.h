#pragma once
#include "simpleserver.h"

struct PentagoClientObj
{
	PentagoClientObj()
	{
		sock = NULL;
		PartnerID = 0;
		ID = 0;
		isPaired = false;
		waitingTime = 0;
	}

	SOCKET sock;
	int ID, PartnerID;
	bool isPaired;
	long waitingTime;
};

class PentagoServer :
	public SimpleServer
{
public:
	PentagoServer(const std::string& ip);
	virtual ~PentagoServer(void);

	virtual bool listenForNewConnection();
	virtual int setupSockets();
	virtual DWORD run();

protected:

	void addNewClient(PentagoClientObj client);
	void pairupClients(PentagoClientObj* a, PentagoClientObj* b);
	bool serverHasWaitingClients();
	PentagoClientObj* findUnpairedClient();

	typedef std::vector<PentagoClientObj> ClientObjects;
	ClientObjects mConnectedClients;

	long mThreadSleepTime;
};

