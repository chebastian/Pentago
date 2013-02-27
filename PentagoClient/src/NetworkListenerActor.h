#pragma once
#include "networkplayer.h"

class NetworkListenerActor :
	public NetworkPlayer
{
public:
	NetworkListenerActor(PentagoBase* base, GameBoard* board);
	~NetworkListenerActor(void);

	virtual void SendClientMessage(ClientMessage* msg);
};

