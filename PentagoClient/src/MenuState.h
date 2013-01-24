#pragma once
#include "gamestate.h"
#include "SDL.h"
#include "IkeyboardListener.h"


class MenuState :
	public GameState, public IKeyboardListener
{
public:
	MenuState(PentagoBase* base);
	virtual ~MenuState(void);

	virtual void OnEnter();
	virtual void Update(const float& time);
	virtual void Render(SDL_Surface* gs);

	virtual void OnKeyClicked(KeyEvent& evt);
	virtual void OnKeyDown(KeyEvent& evt);
	virtual void OnKeyUp(KeyEvent& evt);

	virtual const int& KeyListenerId()
	{return mStateID;}

private:
	int mCurrIndex;
};

