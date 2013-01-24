#pragma once
#include "SDL.h"

class PentagoBase;

#pragma warning( disable : 4100 )

class GameState
{
public:

	GameState(PentagoBase* game)
	{
		mGame = game;
		mStateID = 0;
	}

	virtual void OnEnter()
	{
	}

	virtual void Update(const float& time)
	{
		float t = 0;

		t += time;

		t = t;
	}

	virtual void Render(SDL_Surface* gs)
	{

	}

	virtual void OnExit()
	{
	}

	virtual ~GameState(void)
	{
	}


protected:
	PentagoBase* mGame;
	int mStateID;

};

