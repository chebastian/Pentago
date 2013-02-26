#include "BoardActor.h"
#include "ClientBase.h"
#include "IMessageReceiver.h"

BoardActor::BoardActor(PentagoBase* base,GameBoard* board)
{
	mGame = base;
	mBoard = board;
	mElapsedTime = 0;
	mListeners = Receivers();
}


BoardActor::~BoardActor(void)
{
}

void BoardActor::AddReceiver(IMessageReceiver* receiver)
{
	mListeners.push_back(receiver);
}

void BoardActor::RemoveReceiver(IMessageReceiver* receiver)
{
	for(size_t i = 0; i < mListeners.size(); i++)
	{
		if(mListeners.at(i)->ReceiverID() == receiver->ReceiverID())
		{
			mListeners.erase(mListeners.begin() + i);
			return;
		}
	}

	bool kuken = false;
	kuken = true;
}

void BoardActor::RemoveAllReceivers()
{
	mListeners.clear();
}

void BoardActor::SendClientMessage(ClientMessage* msg)
{
	for(size_t i = 0; i < mListeners.size(); i++)
	{
		mListeners.at(i)->ProcessMessage(msg);
	}
}

void BoardActor::SendClientMessageTo(ClientMessage* msg, const int id)
{
	for(size_t i = 0; i < mListeners.size(); i++)
	{
		if(mListeners.at(i)->ReceiverID() == id)
			mListeners.at(i)->ProcessMessage(msg);
		//mListeners.at(i)->ProcessMessage(msg);
	}
}