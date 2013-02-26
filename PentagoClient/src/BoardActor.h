#pragma once
#include "imessagesender.h"
#include <vector>
#include <string>

struct ClientMessage;
class PentagoBase;
class GameBoard;

class BoardActor 
{
public:
	BoardActor(PentagoBase* base,GameBoard* board);
	virtual ~BoardActor(void);

	virtual void start(){};
	virtual void end(){};

	virtual void AddReceiver(IMessageReceiver* receiver);
	virtual void RemoveReceiver(IMessageReceiver* receiver);
	void		 RemoveAllReceivers();
	virtual void SendClientMessage(ClientMessage* msg);
	virtual void SendClientMessageTo(ClientMessage* msg, const int id);

	virtual void update(const float& time){mElapsedTime += time;}

	const std::string Name(){return ActorName;}
protected:

	std::string ActorName;

	typedef std::vector<IMessageReceiver*> Receivers;
	Receivers mListeners;
	PentagoBase* mGame; 
	GameBoard* mBoard;
	float mElapsedTime;
};

