#pragma once
#include "clientbase.h"

class ChatClient :
	public ClientBase
{
public:
	ChatClient(const std::string& ip);
	~ChatClient(void);

	DWORD run() override;

protected:
	int filmjölk;
};

