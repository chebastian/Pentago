#pragma once
#include "PentagoBase.h"
#include "GameBoard.h"
#include "GameRound.h"
#include "InputManager.h"
#include <vector>
#include <list>
#include "PlaceRound.h"
#include "RotateRound.h"
#include "WinRound.h"
#include "BoardActor.h"
#include "Receivers.h"

class RoundMachine
{
public:

	RoundMachine(PentagoBase* base, GameBoard* board, GameRound* start, BoardActor* first, BoardActor* second)
	{
		mCurrentRound = start;
		mCurrentActor = first;
		//mGame->GetInput()->AddMouseListener(mCurrentRound);
		mCurrentRound->OnEnter();
		mCurrentActor->AddReceiver(start);
		mCurrentIndex = 0;
		//mActors.push_front(mCurrentActor);
		mRounds = Rounds();
		mGame = base;
		mBoard = board;
		mCurrentPlayer = PLAYER_1;
		AddPlayer(second);
	}

	void AddPlayer(BoardActor* actor)
	{
		mActors.push_front(actor);
	}

	BoardActor* CurrentPlayer()
	{
		return mCurrentActor;
	}

	virtual ~RoundMachine(void)
	{
	}

	void InitMachine()
	{
		mCurrentActor->start();
		AddRound(new PlaceRound(mGame,mBoard,mCurrentPlayer));
		AddRound(new WinRound(mGame,mBoard,mCurrentPlayer));
		AddRound(new RotateRound(mGame,mBoard,mCurrentPlayer));
		AddRound(new WinRound(mGame,mBoard,PLAYER_1));
		AddRound(new WinRound(mGame,mBoard,PLAYER_2));
	}

	void AddRound(GameRound* round)
	{
		//mCurrentActor->AddReceiver(round);
		mRounds.push_back(round);
	}

	GameRound* ActiveRound()
	{
		return mCurrentRound;
	}

	void ChangeRound(GameRound* newRound)
	{
		mCurrentRound->OnExit();
		mCurrentActor->RemoveReceiver(mCurrentRound);
		//mGame->GetInput()->RemoveMouseListener(mCurrentRound);

		newRound->OnEnter();
		newRound->setRoundPlayer(mCurrentPlayer);
		mCurrentActor->AddReceiver(newRound);
		//mGame->GetInput()->AddMouseListener(newRound);
		mCurrentRound = newRound;
	}

	void NextRound()
	{
		mCurrentIndex++;
		ChangeRound(getRoundAtIndex(mCurrentIndex));
	}


protected:

	GameRound* getRoundAtIndex(int index)
	{
		if(index >= (int)mRounds.size())
		{
			rotateRound();
			index = 0;
		}

		return mRounds.at(index);
	}

	void rotateRound()
	{
		mCurrentIndex = 0;
		if(mCurrentPlayer == PLAYER_1)
			mCurrentPlayer = PLAYER_2;
		else 
			mCurrentPlayer = PLAYER_1;

		SwitchToNextPlayer();
	}


	void SwitchToNextPlayer()
	{
		mCurrentActor->end();
		AddPlayer(mCurrentActor);
		mCurrentActor = mActors.back();
		mCurrentActor->start();
		mActors.pop_back();

		ClientMessage msg = ClientMessage(ClientMessage::TYPE_NEXT,SFMath::Vector2Di());
		msg.id = SERVER_ID;
		mGame->PlayerClient()->SendClientMessage(msg);
	}

	PLAYER_ID mCurrentPlayer;
	PentagoBase* mGame;
	GameBoard* mBoard;
	GameRound* mCurrentRound;
	typedef std::vector<GameRound*> Rounds;
	BoardActor* mCurrentActor;
	Rounds mRounds;
	int mCurrentIndex;
	std::list<BoardActor*> mActors;
};

