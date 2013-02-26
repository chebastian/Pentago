#pragma once
#include "boardactor.h"
#include "IMessageReceiver.h"
#include "HumanPlayer.h"

class NetworkPlayer :
	public HumanPlayer, public IMessageReceiver
{
public:
	NetworkPlayer(PentagoBase* base, GameBoard* board);
	virtual ~NetworkPlayer(void);

	virtual void start();
	virtual void end();
	virtual void update(const float& time);

	virtual void AddMessage(SFMessage* msg);
	virtual void ProcessMessage(SFMessage* msg);

	virtual int ReceiverID();
	virtual void SendClientMessage(ClientMessage* msg);
protected:
	virtual void OnMessage(SFMessage* msg);
	bool mMyTurn;
};

