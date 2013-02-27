#pragma once
#include "gamestate.h"
#include "IkeyboardListener.h"
#include "RoundMachine.h"

class Entity;
class Board;
class GameBoard;
class NetworkPlayer;

class PlayState :
	public GameState, public IKeyboardListener
{
public:
	PlayState(PentagoBase* base);
	virtual ~PlayState(void);

	virtual void OnEnter();
	virtual void Update(const float& time);
	virtual void Render(SDL_Surface* gs);

	virtual void OnExit();

	virtual void OnKeyClicked(KeyEvent& evt){};
	virtual void OnKeyDown(KeyEvent& evt);
	virtual void OnKeyUp(KeyEvent& evt){};

	virtual const int& KeyListenerId();

protected:
	void setupPlayers();

	Entity* mEntity;
	std::string mMsg;
	GameBoard* mGameBoard;
	RoundMachine* mRoundMachine;
	NetworkPlayer* mPlayerOne, *mPlayerTwo;
};

