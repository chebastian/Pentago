#ifndef CLIENT_MESSAGE_H
#define CLIENT_MESSAGE_H

struct ClientMessage : public SFMessage 
{
	enum TYPE
	{
		TYPE_ONE,
		TYPE_TWO,
		TYPE_SETUP_GAME,
		TYPE_PLACED,
		TYPE_ROTATED,
		TYPE_FINISHED_MOVE,
		TYPE_NEXT,
		NUM_TYPES
	};

	ClientMessage()
	{
		x = 0; y = 0;
		MsgType = TYPE_ONE;
	}

	ClientMessage(TYPE t, const SFMath::Vector2Di& pos)
	{
		MsgType = t;
		x = pos.x;
		y = pos.y;
	}

	TYPE MsgType;
	char text[256];
	int message;
	int x;
	int y;

public:
	int id;
};


#endif