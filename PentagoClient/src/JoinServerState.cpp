#include "JoinServerState.h"
#include "PentagoBase.h"
#include "InputManager.h"
JoinServerState::JoinServerState(PentagoBase* base)
	:GameState(base)
{
	mConnected = false;
	mMsg = "";
	SDLWrapper::GetInstance()->GetInput()->AddKeyboardListener(this);
}


JoinServerState::~JoinServerState(void)
{
	SDLWrapper::GetInstance()->GetInput()->RemoveKeyboardListener(this);
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

		SDLWrapper::GetInstance()->RenderString(mMsg, 10,40);
	}

}

void JoinServerState::OnKeyDown(KeyEvent& evt)
{
	std::string validChars = "qwertyuiopasdfghjklzxcvbnm,.";

	if( validChars.find(evt.keyChar) != std::string::npos)
		mMsg += evt.keyChar;

	if(evt.KeyCode == Key_Code::KC_DOWN)
	{
		mClient->SendMessageToServer(mMsg);
		mMsg = "";
	}
}

const int& JoinServerState::KeyListenerId()
{
	return mStateID;
}

