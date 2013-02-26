#pragma once
#include "PentagoBase.h"
#include "GameBoard.h"
#include "IMouseListener.h"
#include "IMessageReceiver.h"
#include "BoardActor.h"

enum PLAYER_ID
{
	PLAYER_1,
	PLAYER_2
};

class GameRound : public IMouseListener, public IMessageReceiver
{
public:
	
	GameRound(PentagoBase* base, GameBoard* board, const PLAYER_ID playerID)
	{
		m_pGame = base; 
		m_pBoard = board;
		mDone = false;
		mPlayerID = playerID;
		mRoundID = 456;
	}

	GameRound(PentagoBase* base, GameBoard* board)
	{
		m_pGame = base; 
		m_pBoard = board;
		mDone = false;
		mPlayerID = PLAYER_ID::PLAYER_1;
		mRoundID = 456;
	}

	GameRound(GameRound&& other)
		:m_pGame(other.m_pGame),m_pBoard(other.m_pBoard),
		mDone(other.mDone),mPlayerID(other.mPlayerID)
	{
		std::cout << "Move called on gameround" << std::endl;
	}

	virtual ~GameRound(void)
	{
		m_pBoard = NULL;
		m_pGame = NULL;
	}

	void setRoundPlayer(const PLAYER_ID id)
	{
		mPlayerID = id;
	}

	virtual void OnEnter(){}
	virtual void OnUpdate(const float& time){}
	virtual void OnRender(SDL_Surface* gs){}
	virtual void OnExit(){}

	virtual bool isDone(){return mDone;}

	virtual void OnClicked(const SFMouse* mouse){};
	virtual void OnMouseOver(const SFMouse* mouse){};
	virtual void OnMouseDown(const SFMouse* mouse){};
	virtual void OnMouseReleased(const SFMouse* mouse){};
	virtual void OnMouseMove(const SFMouse* mouse){};
	virtual void OnMouseDrag(const SFMouse* mouse){};

	virtual bool CheckMouseOver(const SFMouse* mouse){return true;};	

	virtual const int& MouseListenerId(){return mRoundID;};
	virtual const int& ListenerPriority(){return mRoundID;};

	virtual void AddMessage(SFMessage* msg){};
	virtual void ProcessMessage(SFMessage* msg){};

	virtual int ReceiverID(){return mRoundID;}

	GameRound& operator=(const GameRound& other)
	{
		std::cout << "operator = called on game round" << std::endl;
		m_pBoard = other.m_pBoard;
		m_pGame = other.m_pGame;
		mDone = other.mDone;
		mPlayerID = other.mPlayerID;
	}
protected:
	
	virtual void OnMessage(SFMessage* msg){};

	GameBoard* m_pBoard;
	PentagoBase* m_pGame;
	int mRoundID;
	bool mDone;
	int mPlayerID;
};

