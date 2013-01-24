#include "MenuState.h"
#include "SDLWrapper.h"
#include "JoinServerState.h"
#include "PentagoBase.h"
#include "InputManager.h"

MenuState::MenuState(PentagoBase* base)
	:GameState(base)
{
	mCurrIndex = 0;
	mStateID = 1;
	SDLWrapper::GetInstance()->GetInput()->AddKeyboardListener(this);
}


MenuState::~MenuState(void)
{
	SDLWrapper::GetInstance()->GetInput()->RemoveKeyboardListener(this);
}

void MenuState::OnEnter()
{
}

void MenuState::Update(const float& time)
{

}

void MenuState::Render(SDL_Surface* gs)
{
	SDLWrapper::GetInstance()->RenderString("Pentago Base",10,10);


	std::string vals[] = {std::string("Quick Match"),
						std::string("Join Game"),
						std::string("Exit")};

	for(int i = 0; i < 3; i++)
	{
		if(i == mCurrIndex)
		{
			SDLWrapper::GetInstance()->RenderString(vals[i],20,30 + 20*i,0xFF0000);
			SDLWrapper::GetInstance()->RenderString(">",10,30 + 20*i,0xFF0000);
		}
		else
			SDLWrapper::GetInstance()->RenderString(vals[i],10,30 + 20*i);
	}
}

void MenuState::OnKeyClicked(KeyEvent& evt)
{
}

void MenuState::OnKeyDown(KeyEvent& evt)
{
	if(evt.KeyCode == Key_Code::KC_UP)
	{
		mCurrIndex--;
	}
	else if(evt.KeyCode == Key_Code::KC_DOWN)
	{
		mCurrIndex++;
	}
	else if(evt.KeyCode == Key_Code::KC_SPACE)
	{
		if(mCurrIndex == 1)
		{
			mGame->ChangeState(new JoinServerState(mGame));
		}
		if(mCurrIndex == 2)
			SDLWrapper::GetInstance()->ShutDown();
	}

	if(mCurrIndex > 2 || mCurrIndex < 0)
		mCurrIndex = 0;
}

void MenuState::OnKeyUp(KeyEvent& evt)
{
}