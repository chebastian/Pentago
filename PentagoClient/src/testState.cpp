#include "testState.h"
#include "PentagoBase.h"
#include "ClientBase.h"
#include "ClientPlayer.h"
#include "Board.h"
#include "InputManager.h"
#include "GameBoard.h"
#include "PlaceRound.h"
#include "RotateRound.h"
#include "RoundMachine.h"
#include "HumanPlayer.h"
#include "AgentPlayer.h"


testState::testState(PentagoBase* base)
	:GameState(base)
{
	mStateID = 2354;
}


testState::~testState(void)
{
}

void testState::OnEnter()
{
	mGame->GetInput()->AddMouseListener(this);

	mGameBoard = new GameBoard();
	mGameBoard->initBoard();
	mCurrentPlayer = PLAYER_ID::PLAYER_1;

	mActor = new AgentPlayer(mGame, mGameBoard);
	mRoundMachine = new RoundMachine(mGame,mGameBoard, new PlaceRound(mGame,mGameBoard,PLAYER_1),mActor);
	mRoundMachine->AddPlayer(new HumanPlayer(mGame,mGameBoard));
	mRoundMachine->InitMachine();

	//mGame->GetInput()->AddMouseListener((HumanPlayer*)mActor);
}

void testState::OnExit()
{
	mGame->GetInput()->RemoveMouseListener(this);
}

void testState::Update(const float& time)
{

	mRoundMachine->CurrentPlayer()->update(time);
	if(mRoundMachine->ActiveRound()->isDone())
		mRoundMachine->NextRound();

	mRoundMachine->ActiveRound()->OnUpdate(time);

}

void testState::Render(SDL_Surface* gs)
{
	mGameBoard->Render(gs);
	mRoundMachine->ActiveRound()->OnRender(gs);
}

void testState::OnClicked(const SFMouse* mouse)
{
}

void testState::OnMouseOver(const SFMouse* mouse)
{
}

void testState::OnMouseDown(const SFMouse* mouse)
{
	
}

void testState::OnMouseReleased(const SFMouse* mouse)
{

}


void testState::OnMouseMove(const SFMouse* mouse)
{
	
}
void testState::OnMouseDrag(const SFMouse* mouse)
{
}

bool testState::CheckMouseOver(const SFMouse* mouse)
{
	return true;
}

const int& testState::MouseListenerId()
{
	return mStateID;
}

const int& testState::ListenerPriority()
{
	return mStateID;
}