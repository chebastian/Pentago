#include "MessageManager.h"
#include "SFMessage.h"
#include <algorithm>

MessageManager::MessageManager(void)
{
}


MessageManager::~MessageManager(void)
{
}

void MessageManager::RegisterReceiver(IMessageReceiver* receiver)
{
	/*std::vector<IMessageReceiver*>::iterator iter = std::find(mRegistratedReceivers.begin(), mRegistratedReceivers.end(), receiver);

	if(iter == mRegistratedReceivers.end())
		mRegistratedReceivers.push_back(receiver);*/

	std::vector<IMessageReceiver*>::iterator iter = std::find(mRegistratedReceivers.begin(), mRegistratedReceivers.end(), receiver);

	if(iter == mRegistratedReceivers.end())
		mNewReceivers.push_back(receiver);
}

void MessageManager::UnregisterReceiver(IMessageReceiver* receiver)
{
	for(VecReceivers::iterator iterB = mRegistratedReceivers.begin(); iterB != mRegistratedReceivers.end(); iterB++)
	{
		if(receiver->ReceiverID() == (*iterB)->ReceiverID())
		{
			mRegistratedReceivers.erase(iterB);
			return;
		}
	}

	for(VecReceivers::iterator iterB = mNewReceivers.begin(); iterB != mNewReceivers.end(); iterB++)
	{
		if(receiver->ReceiverID() == (*iterB)->ReceiverID())
		{
			mNewReceivers.erase(iterB);
			return;
		}
	}
}

void MessageManager::AddMessage( SFMessage* msg )
{
	/*mMessages.push_back(*msg);

	std::vector<std::string>::iterator iter = std::find(mReceivers.begin(), mReceivers.end(), msg->Sender());

	if(iter == mReceivers.end())
		mReceivers.push_back(msg->Sender());*/

	mNewMessages.push_back(*msg);
}

void MessageManager::ProcessMessages( float time )
{
	//
	//Add new Messages and receivers
	//

	for(MsgVec::iterator iter = mNewMessages.begin(); iter != mNewMessages.end(); iter++)
	{
		mMessages.push_back((*iter));
	}
	mNewMessages.clear();

	for(VecReceivers::iterator iter = mNewReceivers.begin(); iter != mNewReceivers.end(); iter++)
	{
		mRegistratedReceivers.push_back((*iter));
	}
	mNewReceivers.clear();




	//
	//Process active messages
	//
	for(MsgIter iter = mMessages.begin(); iter != mMessages.end();)
	{
		this->ProcessDelayedMessage((*iter) ,time);

		MsgIter next = iter;
		next++;

		SFMessage msg = (*iter);
		if(msg.To() == NULL && msg.delay <= 0.0f )
		{
			//std::vector<std::string>::iterator resiter = mReceivers.begin();
			IterReceiver resiter = mRegistratedReceivers.begin();
			for(resiter; resiter != mRegistratedReceivers.end(); resiter++)
			{
				(*resiter)->AddMessage(&msg);
				(*resiter)->ProcessMessage(&msg);
				//REMOVE

			}
			next = mMessages.erase(iter);

		}
		else if(msg.To() != NULL && msg.delay <= 0.0f)
		{
			msg.To()->AddMessage(&msg);
			msg.To()->ProcessMessage(&msg);
			next = mMessages.erase(iter);
		}

		iter = next;
	}

	//
	//Remove receivers that may have been erased during processing of msg's
	//
/*
	for(VecReceivers::iterator iter = mRemovedReceivers.begin(); iter != mRemovedReceivers.end(); iter++)
	{
		for(VecReceivers::iterator iterB = mRegistratedReceivers.begin(); iterB != mRegistratedReceivers.end(); iterB++)
		{
			if((*iter)->ReceiverID() == (*iterB)->ReceiverID())
			{
				mRegistratedReceivers.erase(iterB);
				break;
			}
		}
	}
	mRemovedReceivers.clear();*/
}

void MessageManager::ProcessDelayedMessage( SFMessage& msg , float time)
{
	if(msg.delay >= 0.0)
	{
		msg.delay -= time;
	}
}

IMessageReceiver* MessageManager::GetReceiver( const int& id )
{
	//Entity* ent = EntityManager::GetInstance()->GetEntity(id);

	IMessageReceiver* rec = NULL;

	for(IterReceiver iter = mRegistratedReceivers.begin(); iter != mRegistratedReceivers.end(); iter++)
	{
		if((*iter)->ReceiverID() == id)
		{
			rec = (*iter);
			return rec;
		}
	}

	return NULL;
}

bool MessageManager::RemoveMessage( SFMessage* msg )
{
	int counter = 0;
	for(MsgIter iter = mMessages.begin(); iter != mMessages.end(); iter++)
	{
		if((*iter).Id() == msg->Id())
		{
			mMessages.erase(iter);
			return true;
		}

		counter++;
	}

		return false;
}