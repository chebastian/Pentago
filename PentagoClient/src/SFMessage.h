#ifndef SFMESSAGE_H
#define SFMESSAGE_H

class IMessageReceiver;
class IMessageSender;


class SFMessage
{
public:

	SFMessage(void)
	{
		from = NULL;
		to = NULL;
		mID = 0;
		delay = 0.0f;
	}

	virtual ~SFMessage(void)
	{
	}

	IMessageReceiver * To()
	{
		return to;
	}
	

	const int Id()
	{
		return mID;
	}
	float delay;

protected:
	int mID;
	IMessageSender* from;
	IMessageReceiver* to;
	
};

#endif
