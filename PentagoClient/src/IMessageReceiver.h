#pragma once

#include <string>

class SFMessage;

class IMessageReceiver
{
public:
	virtual void AddMessage(SFMessage* msg) = 0;
	virtual void ProcessMessage(SFMessage* msg) = 0;

	virtual std::string ReceiverID() = 0;
protected:
	virtual void OnMessage(SFMessage* msg) = 0;
};