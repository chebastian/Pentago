#include "JoinServerState.h"
#include "PentagoBase.h"
#include "InputManager.h"
#include "PlayState.h"

JoinServerState::JoinServerState(PentagoBase* base)
	:GameState(base)
{
	mConnected = false;
	mMsg = "";
	mStateID = 2312141;
	SDLWrapper::GetInstance()->GetInput()->AddKeyboardListener(this);
}

JoinServerState::~JoinServerState(void)
{
	SDLWrapper::GetInstance()->GetInput()->RemoveKeyboardListener(this);
}

void JoinServerState::OnEnter()
{
	mClient = mGame->PlayerClient();
	mClient->initWinSock();
	mClient->setupSockets(true);
	if(mClient->connectToServer() == RETURN_OK)
	{
		mConnected = mClient->ConnectedToServer();
	}
}

void JoinServerState::Update(const float& time)
{
		
}

void JoinServerState::Render(SDL_Surface* gs)
{
	if(!mClient->ConnectedToServer() || !mClient->PartnerFound())
	{
		SDLWrapper::GetInstance()->RenderString("Waiting for server...", 0,0);
	}
	else
	{
		mConnected = true;
		SDLWrapper::GetInstance()->RenderString("Connection etablished", 0,0);
		SDLWrapper::GetInstance()->RenderString(mClient->latestMsgFromServer(), 10,20);

		SDLWrapper::GetInstance()->RenderString(mMsg, 10,SDLWrapper::GetInstance()->Screen()->h - 20);
		mGame->ChangeState(new PlayState(mGame));
	}
}

void JoinServerState::OnKeyDown(KeyEvent& evt)
{
	std::string validChars = "qwertyuiopasdfghjklzxcvbnm,.1234567890 ";

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

