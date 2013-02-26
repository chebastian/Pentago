#pragma once
#include "gameround.h"
#include "IkeyboardListener.h"

class WinRound :
	public GameRound, public IKeyboardListener
{
public:
	WinRound(PentagoBase* base, GameBoard* board,const PLAYER_ID playerID);
	virtual ~WinRound(void);

	virtual void OnEnter();
	virtual void OnUpdate(const float& time);
	virtual void OnRender(SDL_Surface* gs);
	virtual void OnExit();

	virtual void OnKeyClicked(KeyEvent& evt){};
	virtual void OnKeyDown(KeyEvent& evt);
	virtual void OnKeyUp(KeyEvent& evt){};

	virtual const int& KeyListenerId(){return mRoundID;}


	bool mHasWon;
	sStone::Type mWinner;
};

