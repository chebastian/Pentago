#include "PlaceRound.h"
#include "InputManager.h"
#include "SDLWrapper.h"
#include "ClientBase.h"
#include "Receivers.h"

PlaceRound::PlaceRound(PentagoBase* base, GameBoard* board,const PLAYER_ID playerID)
	:GameRound(base,board,playerID)
{
	mRoundID = ROUND_ID;
}


PlaceRound::~PlaceRound(void)
{
}

void PlaceRound::OnEnter()
{
	mDone = false;
}

void PlaceRound::OnUpdate(const float& time)
{
}

void PlaceRound::OnRender(SDL_Surface* gs)
{
	SDLWrapper::GetInstance()->RenderString("Place your stone", 10,400);
}

void PlaceRound::OnExit()
{
}

void PlaceRound::OnMouseDown(const SFMouse* mouse)
{
	SFMath::Vector2Di pos(0,0);
	pos.x = (int)m_pGame->GetInput()->GetMouseXY().x;
	pos.y = (int)m_pGame->GetInput()->GetMouseXY().y;
	/*sStone stone = sStone(sStone::EMPTY);
	
	if(mPlayerID == PLAYER_1)
		stone.value = sStone::P1;
	else
		stone.value = sStone::P2;

	bool validMove = m_pBoard->playerPlaceStoneAtScreenPos(pos,stone);

	if(validMove)
		mDone = true;*/
	//PlaceStoneOnBoard(pos);
}

void PlaceRound::PlaceStoneOnBoard(const SFMath::Vector2Di& pos)
{
	sStone stone = sStone(sStone::EMPTY);
	
	if(mPlayerID == PLAYER_1)
		stone.value = sStone::P1;
	else
		stone.value = sStone::P2;

	bool validMove = m_pBoard->playerPlaceStoneAtScreenPos(pos,stone);

	if(validMove)
		mDone = true;
}

void PlaceRound::ProcessMessage(SFMessage* msg)
{
	ClientMessage* cmsg = dynamic_cast<ClientMessage*>(msg);

	if(cmsg->MsgType == ClientMessage::TYPE_FINISHED_MOVE)
	{
		SFMath::Vector2Di pos(0,0);
		pos.x = cmsg->x;
		pos.y = cmsg->y;
		PlaceStoneOnBoard(pos);
	}
}
