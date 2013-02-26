#include "NetworkPlayer.h"
#include "PentagoBase.h"
#include "ClientPlayer.h"
#include "Receivers.h"

NetworkPlayer::NetworkPlayer(PentagoBase* base, GameBoard* board)
	:HumanPlayer(base,board)
{
	ActorName = "undefined";
	mMyTurn = false;
}


NetworkPlayer::~NetworkPlayer(void)
{
}


void NetworkPlayer::start()
{
	AddReceiver(mGame->PlayerClient());
}

void NetworkPlayer::end()
{
	RemoveReceiver(mGame->PlayerClient());
}

void NetworkPlayer::update(const float& time)
{
	//ClientMessage msg = mGame->PlayerClient()->GetLatestPacketFromServer();		
	/*if(mGame->PlayerClient()->hasNewMessage())
	{
		ClientMessage msg = mGame->PlayerClient()->GetLatestPacketFromServer();
		msg = msg;
		SendClientMessage(&msg);
	}*/
}	

void NetworkPlayer::AddMessage(SFMessage* msg)
{
}

void NetworkPlayer::ProcessMessage(SFMessage* msg)
{
	ClientMessage* cmsg = dynamic_cast<ClientMessage*>(msg);
	if(cmsg->id == ROUND_ID && cmsg->MsgType == ClientMessage::TYPE_FINISHED_MOVE)
	{
		SendClientMessageTo(cmsg,ROUND_ID);
	}

	std::cout << "Recv: msg" << cmsg->message << std::endl;

	if(cmsg->id == SERVER_ID && cmsg->MsgType == ClientMessage::TYPE_SETUP_GAME)
	{
		ActorName = std::string("Player");
		ActorName += (char)cmsg->message;

		std::cout << "Recv: setup" << std::endl;
		mMyTurn = true;
	}

	if(cmsg->id == SERVER_ID && cmsg->MsgType == ClientMessage::TYPE_NEXT)
		mMyTurn = !mMyTurn;
	//SendClientMessage(cmsg);
}

void NetworkPlayer::SendClientMessage(ClientMessage* msg)
{
	if(mMyTurn)
		BoardActor::SendClientMessage(msg);
}

void NetworkPlayer::OnMessage(SFMessage* msg)
{
}

int NetworkPlayer::ReceiverID()
{
	return 0;
}
