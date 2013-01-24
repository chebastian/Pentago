#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "SDL.h"
#include "SDLWrapper.h"
#include "IkeyboardListener.h"


class PentagoBase : public IKeyboardListener
{
public:
	PentagoBase(void);
	~PentagoBase(void);

	void initGameSystem();
	bool updateGameSystem();
	void render();

	void ChangeState(GameState* state);

	virtual void OnKeyClicked(KeyEvent& evt);
	virtual void OnKeyDown(KeyEvent& evt);
	virtual void OnKeyUp(KeyEvent& evt);

	virtual const int& KeyListenerId();

private:

	int mCurrIndex;
	GameStateManager* mGameStateMgr;
	int mID;
};

