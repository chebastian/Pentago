#include "JoinServerState.h"
#include "PentagoBase.h"

JoinServerState::JoinServerState(PentagoBase* base)
	:GameState(base)
{
	mConnected = false;
}


JoinServerState::~JoinServerState(void)
{
}

void JoinServerState::OnEnter()
{
	mClient = new ClientBase("127.0.0.1");
	mClient->initWinSock();
	mClient->setupSockets();
	if(mClient->connectToServer() == RETURN_OK)
	{
		mConnected = true;
		mClient->itShouldReceiveServerMsg();
	}
}

void JoinServerState::Update(const float& time)
{

}

void JoinServerState::Render(SDL_Surface* gs)
{
	if(!mConnected)
	{
		SDLWrapper::GetInstance()->RenderString("Waiting for server...", 0,0);
	}
	else
	{
		SDLWrapper::GetInstance()->RenderString("Connection etablished", 0,0);
		SDLWrapper::GetInstance()->RenderString(mClient->latestMsgFromServer(), 10,20);
	}

}

