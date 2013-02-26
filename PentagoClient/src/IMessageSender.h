#pragma once

#include <string>
class SFMessage;
class IMessageReceiver;

class IMessageSender
{
protected:

	virtual void AddReceiver(IMessageReceiver* receiver) = 0;
	virtual void SendMessage(SFMessage* msg) = 0;
	virtual void SendMessage(const std::string& message, const std::string& to, float t) = 0;

	virtual void SendGlobalMessage(SFMessage* msg) = 0;
	virtual void SendGlobalMessage(const std::string& message, float t) = 0;
};