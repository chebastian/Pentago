#pragma once
#include "gameround.h"

class PlaceRound :
	public GameRound
{
public:
	PlaceRound(PentagoBase* base, GameBoard* board,const PLAYER_ID playerID);
	virtual ~PlaceRound(void);

	virtual void OnEnter();
	virtual void OnUpdate(const float& time);
	virtual void OnRender(SDL_Surface* gs);
	virtual void OnExit();
	virtual void OnMouseDown(const SFMouse* mouse);

	virtual void ProcessMessage(SFMessage* msg);

protected:
	void PlaceStoneOnBoard(const SFMath::Vector2Di& pos);
};

