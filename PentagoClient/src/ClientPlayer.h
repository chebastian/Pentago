#pragma once
#include "clientbase.h"
#include "IMessageReceiver.h"
#include "IMessageSender.h"

#define PLAYER_ONE 0
#define PLAYER_TWO 1

class ClientPlayer :
	public ClientBase, public IMessageReceiver
{
public:
	ClientPlayer(const std::string& ip);
	virtual ~ClientPlayer(void);

	virtual int connectToServer();
	DWORD run() override;

	void SendClientMessage(ClientMessage msg);

	ClientMessage GetLatestPacketFromServer();
	bool isConnectedToPartner();
	const bool hasNewMessage();

	void addServerMessageListener(IMessageReceiver* recv);
	void HandleIncomingMessageFromServer(ClientMessage msg);

	const bool IsPlayerOne()
	{
		return mPlayerID == PLAYER_ONE;
	}
	
	const bool PartnerFound()
	{
		return mFoundPartner;
	}

protected:
	const bool LatestMessageRead();
	void SendMessageToListeners(ClientMessage msg);

	void handleMessagesFromOtherClients();
	bool waitForServerResponse(int maxRetry);

	virtual void AddMessage( SFMessage* msg );

	virtual void ProcessMessage( SFMessage* msg );

	virtual int ReceiverID();

	virtual void OnMessage( SFMessage* msg );

	bool mFoundPartner;
	ClientMessage mLatestPacket;
	bool mHasNewMessage;
	bool mLatestMessageRead;
	int mPlayerID;
	std::vector<IMessageReceiver*> mListeners;
};

