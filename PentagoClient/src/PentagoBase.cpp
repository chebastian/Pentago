#include "PentagoBase.h"
#include "InputManager.h"
#include "KeyEvent.h"
#include <string>
#include "MenuState.h"
#include "testState.h"

PentagoBase::PentagoBase(void)
{
	mCurrIndex = 0;
	mID = 0;
	mGameStateMgr = new GameStateManager(this);
	mGameStateMgr->ChangeState(new MenuState(this));
	mPlayerClient = new ClientPlayer("127.0.0.1");
}


PentagoBase::~PentagoBase(void)
{
	SDLWrapper::GetInstance()->ShutDown();
}

void PentagoBase::initGameSystem()
{
	SDLWrapper::GetInstance()->Initialize();
	SDLWrapper::GetInstance()->GetInput()->AddKeyboardListener(this);
}

bool PentagoBase::updateGameSystem()
{
	mGameStateMgr->ActiveState()->Update(SDLWrapper::GetInstance()->ElapsedTime());
	return 	SDLWrapper::GetInstance()->Update();
}

void PentagoBase::render()
{
	mGameStateMgr->ActiveState()->Render(SDLWrapper::GetInstance()->Screen());
}

void PentagoBase::ChangeState(GameState* state)
{
	mGameStateMgr->ChangeState(state);
}

void PentagoBase::OnKeyClicked(KeyEvent& evt)
{
	
}

void PentagoBase::OnKeyDown(KeyEvent& evt)
{
	
}

void PentagoBase::OnKeyUp(KeyEvent& evt)
{
}

const int& PentagoBase::KeyListenerId()
{
	return mID;
}

InputManager* PentagoBase::GetInput()
{
	return SDLWrapper::GetInstance()->GetInput();
}

ClientPlayer* PentagoBase::PlayerClient()
{
	return mPlayerClient;
}

SFMath::Vector2Di PentagoBase::ScreenSize()
{
	SFMath::Vector2Di sz = SFMath::Vector2Di();
	sz.x = SDLWrapper::GetInstance()->Screen()->w;
	sz.y = SDLWrapper::GetInstance()->Screen()->h;
	return sz;
}