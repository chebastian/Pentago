#include "ChatClient.h"


ChatClient::ChatClient(const std::string& ip)
	:ClientBase(ip)
{
}


ChatClient::~ChatClient(void)
{
}

DWORD ChatClient::run()
{
	return 0;
}