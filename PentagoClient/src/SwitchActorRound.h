#pragma once
#include "gameround.h"

class SwitchActorRound :
	public GameRound
{
public:
	SwitchActorRound(PentagoBase* base, GameBoard* board);
	virtual ~SwitchActorRound(void);

	virtual void OnEnter();
	virtual void OnUpdate( const float& time );
	virtual void OnRender( SDL_Surface* gs );
	virtual void OnExit();

	virtual void ProcessMessage( SFMessage* msg );
};

