#pragma once
#include "clientbase.h"

class ChatClient :
	public ClientBase
{
public:
	ChatClient(const std::string& ip);
	~ChatClient(void);

	virtual int connectToServer();
	DWORD run() override;

	bool newMessageRcvdFromServer();

protected:
};

