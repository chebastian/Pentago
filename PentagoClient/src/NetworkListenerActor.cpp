#include "NetworkListenerActor.h"


NetworkListenerActor::NetworkListenerActor(PentagoBase* base, GameBoard* board)
	:NetworkPlayer(base,board)
{

}


NetworkListenerActor::~NetworkListenerActor(void)
{
}


void NetworkListenerActor::SendClientMessage(ClientMessage* msg)
{
	//DO NOTHING
}