#pragma once
#include "GameState.h"
#include "GameStateManager.h"
#include "SDL.h"
#include "SDLWrapper.h"
#include "IkeyboardListener.h"
#include "ClientPlayer.h"

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

	InputManager* GetInput();
	ClientPlayer* PlayerClient();

	SFMath::Vector2Di ScreenSize();

private:
	ClientPlayer* mPlayerClient;
	int mCurrIndex;
	GameStateManager* mGameStateMgr;
	int mID;
};

