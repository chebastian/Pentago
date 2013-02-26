#include "WinRound.h"
#include "SDLWrapper.h"
#include "InputManager.h"

WinRound::WinRound(PentagoBase* base, GameBoard* board,const PLAYER_ID playerID)
	:GameRound(base,board,playerID)
{
	mHasWon = false;
	mDone = false;
}


WinRound::~WinRound(void)
{
}

void WinRound::OnEnter()
{
	mHasWon = false;
	mDone = false;
	m_pGame->GetInput()->AddKeyboardListener(this);
}

void WinRound::OnUpdate(const float& time)
{
	sStone::Type t = mPlayerID == PLAYER_1 ? sStone::P1 : sStone::P2;
	int winningNumber  = 4;
	if(m_pBoard->getMaxStonesInCol(t) > winningNumber ||
		m_pBoard->getMaxStonesInRow(t) > winningNumber ||
		m_pBoard->getMaxStonesInDir(SFMath::Vector2Di(1,1),t) > winningNumber ||
		m_pBoard->getMaxStonesInDir(SFMath::Vector2Di(-1,1),t) > winningNumber)
	{
		mWinner = t;
		mHasWon = true;
		mDone = false;
	}
	else
		mDone = true;
}

void WinRound::OnRender(SDL_Surface* gs)
{
	std::string player1 = "Player1";
	std::string player2 = "Player2";
	std::string winner = mPlayerID == mWinner ? player1 : player2;

	if(mHasWon)
	{
		SDLWrapper::GetInstance()->RenderString("A WINNER IS YOU!!!!",150,150);
		SDLWrapper::GetInstance()->RenderString("Press Y to replay or go die!!!!",150,170,0x000000);
	}
}

void WinRound::OnExit()
{
	mDone = false;
	mHasWon = false;
	m_pGame->GetInput()->RemoveKeyboardListener(this);
}

void WinRound::OnKeyDown(KeyEvent& evt)
{
	if(mHasWon)
	{
		if(evt.keyChar == 'y')
		{
			m_pBoard->resetBoard();
			mDone = true;
		}
		else if(evt.keyChar == 'n')
		{

		}
	}
}