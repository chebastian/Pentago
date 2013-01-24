#pragma once

#include <functional>
#include <vector>
#include <memory>
#include "GameState.h"

class PentagoBase;

class GameStateManager
{
public:

	GameStateManager(PentagoBase* game)
	{
		mGame = game;
		mCurrentState = new GameState(game);
	}

	~GameStateManager(void)
	{
		if(mCurrentState)
			delete mCurrentState;
	}

	void ChangeState(GameState* gs)
	{
		if(mCurrentState != NULL)
		{
			mCurrentState->OnExit();
			delete mCurrentState;
		}

		mCurrentState = gs;
		mCurrentState->OnEnter();
	}

	GameState* ActiveState()
	{
		return mCurrentState;
	}

	void CleanUp()
	{
		delete mCurrentState;
		mStates.clear();
	}

protected:
	typedef std::shared_ptr<GameState> GameStatePtr;

	GameState* mCurrentState;
	std::vector<GameStatePtr> mStates;

	PentagoBase* mGame;
};

