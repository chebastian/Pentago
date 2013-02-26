#pragma once

#include "IMessageReceiver.h"
#include "IMessageSender.h"
#include <vector>
#include <map>

class SFMessage;

class MessageManager
{
public:
	MessageManager(void);
	~MessageManager(void);

	void RegisterReceiver(IMessageReceiver* receiver);
	void UnregisterReceiver(IMessageReceiver* receiver);

	void AddMessage(SFMessage* msg);
	void ProcessMessages(float time);
	bool RemoveMessage(SFMessage* msg);

	static MessageManager* GetInstance()
	{
		static MessageManager instance = MessageManager();
		return &instance;
	}

private:
	void ProcessDelayedMessage( SFMessage& msg , float time);

	IMessageReceiver* GetReceiver(const int& id);


	typedef std::vector<IMessageReceiver*>::iterator IterReceiver;
	typedef std::vector<IMessageReceiver*> VecReceivers;
	typedef std::vector<SFMessage>::iterator MsgIter;
	typedef std::vector<SFMessage> MsgVec;
	std::vector<IMessageReceiver*> mRegistratedReceivers;
	VecReceivers mNewReceivers;
	VecReceivers mRemovedReceivers;

	std::vector<std::string> mReceivers;
	std::vector<SFMessage> mMessages;
	MsgVec mNewMessages;
};

#define MessageMgr MessageManager::GetInstance()

