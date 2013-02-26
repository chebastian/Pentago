#pragma once
#include "gamestate.h"
#include "IMouseListener.h"
#include "GameRound.h"

class GameBoard;
class ClientBase;
class Board;
class GameRound;
class RoundMachine;
class BoardActor;

enum PLAYING_STATE
{
	PLACEING,
	ROTATING,
	NEXT_PLAYER,
	WINNING
};

class testState :
	public GameState, public IMouseListener
{
public:
	testState(PentagoBase* base);
	~testState(void);

	virtual void OnEnter();
	virtual void Update(const float& time);
	virtual void Render(SDL_Surface* gs);
	virtual void OnExit();

	virtual void OnClicked(const SFMouse* mouse);
	virtual void OnMouseOver(const SFMouse* mouse);
	virtual void OnMouseDown(const SFMouse* mouse);
	virtual void OnMouseReleased(const SFMouse* mouse);
	virtual void OnMouseMove(const SFMouse* mouse);
	virtual void OnMouseDrag(const SFMouse* mouse);

	virtual bool CheckMouseOver(const SFMouse* mouse);	
	virtual const int& MouseListenerId();
	virtual const int& ListenerPriority();
	
protected:
	ClientBase* mClient;
	Board* mBoard;
	GameBoard* mGameBoard;

	PLAYER_ID mCurrentPlayer;

	BoardActor* mActor;
	RoundMachine* mRoundMachine;
};

