#include "PentagoBase.h"
#include "InputManager.h"
#include "KeyEvent.h"
#include <string>
#include "MenuState.h"
PentagoBase::PentagoBase(void)
{
	mCurrIndex = 0;
	mID = 0;
	mGameStateMgr = new GameStateManager(this);
	mGameStateMgr->ChangeState(new MenuState(this));
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
	mGameStateMgr->ActiveState()->Update(1.0f);
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