#pragma once
#include "simpleserver.h"
#include "SFMessage.h"
#include "Vector2D.h"
#include "../../PentagoClient/src/ClientMessage.h"

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
	void handlePacketsBetweenClients();

protected:

	void addNewClient(PentagoClientObj client);
	void pairupClients(PentagoClientObj* a, PentagoClientObj* b);
	bool serverHasWaitingClients();
	PentagoClientObj* findUnpairedClient();
	int sendClientPacketToClient(int id, ClientMessage& msg);
	void sendSetupInfoToClients(PentagoClientObj* a, PentagoClientObj* b);

	bool messageIsClientPlayer();

	typedef std::vector<PentagoClientObj> ClientObjects;
	ClientObjects mConnectedClients;

	long mThreadSleepTime;
};

