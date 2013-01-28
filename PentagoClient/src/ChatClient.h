#pragma once
#include "clientbase.h"

class ChatClient :
	public ClientBase
{
public:

	typedef std::vector<std::string> Messages;

	ChatClient(const std::string& ip);
	~ChatClient(void);

	virtual int connectToServer();
	DWORD run() override;

	bool newMessageRcvdFromServer();
	Messages getMessages();
protected:

	Messages mMessages;
};

