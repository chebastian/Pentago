#include "HumanPlayer.h"
#include "ClientBase.h"
#include "InputManager.h"
#include "PentagoBase.h"
#include "Receivers.h"

HumanPlayer::HumanPlayer(PentagoBase* base,GameBoard* board)
	:BoardActor(base,board)
{
	mID = 9000;	
}


HumanPlayer::~HumanPlayer(void)
{
}

void HumanPlayer::start()
{
	mGame->GetInput()->AddMouseListener(this);
}

void HumanPlayer::end()
{
	mGame->GetInput()->RemoveMouseListener(this);
}

void HumanPlayer::OnClicked(const SFMouse* mouse)
{
}

void HumanPlayer::OnMouseOver(const SFMouse* mouse)
{
}

void HumanPlayer::OnMouseDown(const SFMouse* mouse)
{
	SFMath::Vector2Di pos(0,0);
	pos.x = mouse->X(); pos.y = mouse->Y();

	ClientMessage msg = ClientMessage(ClientMessage::TYPE_FINISHED_MOVE, pos);
	msg.id = ROUND_ID;
	msg.message = mID;
	SendClientMessage(&msg);
}

void HumanPlayer::OnMouseReleased(const SFMouse* mouse)
{
}

void HumanPlayer::OnMouseMove(const SFMouse* mouse)
{
}

void HumanPlayer::OnMouseDrag(const SFMouse* mouse)
{
}