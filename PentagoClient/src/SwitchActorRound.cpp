#include "SwitchActorRound.h"


SwitchActorRound::SwitchActorRound(PentagoBase* base, GameBoard* board)
	:GameRound(base, board)
{
}


SwitchActorRound::~SwitchActorRound(void)
{
}

void SwitchActorRound::OnEnter()
{
	
}

void SwitchActorRound::OnUpdate( const float& time )
{
	
}

void SwitchActorRound::OnRender( SDL_Surface* gs )
{
	GameRound::OnRender(gs);
}

void SwitchActorRound::OnExit()
{
	
}

void SwitchActorRound::ProcessMessage( SFMessage* msg )
{
	msg = msg;
}
