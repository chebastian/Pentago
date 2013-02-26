#include "RotateRound.h"
#include "InputManager.h"
#include "Receivers.h"

RotateRound::RotateRound(PentagoBase* base, GameBoard* board,const PLAYER_ID playerID)
	:GameRound(base,board,playerID)
{
	mRoundID = ROUND_ID;
}


RotateRound::~RotateRound(void)
{
	delete mRotOrigin;
	SDL_FreeSurface(mToRotate);
}

void RotateRound::OnEnter()
{
	mDone = false;
	mRotated = false;
	mCurrRot = 0.0f;
	mRotationDelta = 0.0f;
	mRotOrigin = new SFMath::Vector2Di(0,0);
	mRotDir = 0;
}

void RotateRound::OnExit()
{
	delete mRotOrigin;
}

void RotateRound::OnUpdate(const float& time)
{
	if(mRotated)
	{
		updateRotation(time);
	}
}

void RotateRound::updateRotation(const float& time)
{
	mCurrRot += mRotDir * (90.0f*time);
	mRotationDelta -= 90.0f*time;

	if(mCurrRot > 359)
		mCurrRot = 0;
}

void RotateRound::OnRender(SDL_Surface* gs)
{
	SDLWrapper::GetInstance()->RenderString("Rotate A Segment", 10,400);
	if(mRotated)
	{	
		RenderRotatedSegment(gs);
	}
	RenderRotationIndicator(mRotIndicatorPos,gs);
}

void RotateRound::RenderRotatedSegment(SDL_Surface* gs)
{
	SDL_Rect src = SDL_Rect();
	src.x = 0; src.y = 0; 
	src.w = (Uint16)mToRotate->w; src.h = (Uint16)mToRotate->h;

	SDL_Surface* rotated = SDLWrapper::GetInstance()->createNewRotatedSurface(mToRotate,src,(int)mCurrRot);
	src.w = (Uint16)rotated->w;
	src.h = (Uint16)rotated->h;

	SDL_Rect dst = SDL_Rect();
	dst.x = (Sint16)mRotOrigin->x;
	dst.y = (Sint16)mRotOrigin->y;
	dst.w = (Uint16)rotated->w;
	dst.h = (Uint16)rotated->h;

	Uint32 ck = SDL_MapRGB(rotated->format,255,0,255);
	SDL_SetColorKey(rotated,SDL_SRCCOLORKEY,ck);

	SDL_BlitSurface(rotated,&src,gs,&dst);
	SDL_FreeSurface(rotated);

	if(abs(mCurrRot) >= 90)
	{
		mDone = true;
		m_pBoard->setSegmentRenderStatus(*mRotOrigin,true);
	}
}

void RotateRound::RenderRotationIndicator(const SFMath::Vector2Di& pos, SDL_Surface* gs)
{
	std::string clockwise = "->";
	std::string anticlockwise = "<-";
	std::string toRender = mRotDir == 1 ? clockwise : anticlockwise;

	SDLWrapper::GetInstance()->RenderString(toRender,pos.x + 20,pos.y,0x000000);
}

void RotateRound::OnMouseDown(const SFMouse* mouse)
{
	if(!mRotated)
	{
		SFMath::Vector2Di pos(0,0);
		pos.x = (int)m_pGame->GetInput()->GetMouseXY().x;
		pos.y = (int)m_pGame->GetInput()->GetMouseXY().y;
		/*sStone stone = sStone(sStone::EMPTY);

		if(m_pBoard->isValidSegmentRotation(pos))
		{
			mToRotate = m_pBoard->createSurfaceToRotate(m_pBoard->screenToSegmentIndex(pos));
			mRotated = true;

			SFMath::Vector2Di segIndex = m_pBoard->screenToSegmentIndex(pos);
			SFMath::Vector2Di offsetPos = SFMath::Vector2Di(pos.x + m_pBoard->getSegmentWidthInPixles()/2,pos.y);
			SFMath::Vector2Di offsetIndex = m_pBoard->screenToSegmentIndex(offsetPos);

			mRotDir = segIndex.x < offsetIndex.x ? 1 : -1;
			mRotOrigin->x = m_pBoard->segmentToScreenIndex(segIndex).x;
			mRotOrigin->y = m_pBoard->segmentToScreenIndex(segIndex).y;
			m_pBoard->setSegmentRenderStatus(pos,false);

			bool clockwise = mRotDir == 1;
			m_pBoard->rotateSegmentAt(pos, clockwise);
		}*/
	}
	//mDone = true;
}

void RotateRound::OnMouseMove(const SFMouse* mouse)
{
	SFMath::Vector2Di mousePos(0,0);

	mousePos.x = mouse->X();
	mousePos.y = mouse->Y();
/*
	mRotIndicatorPos = mousePos;

	SFMath::Vector2Di segIndex = m_pBoard->screenToSegmentIndex(mousePos);
	SFMath::Vector2Di offsetPos = SFMath::Vector2Di(mousePos.x + m_pBoard->getSegmentWidthInPixles()/2,mousePos.y);
	SFMath::Vector2Di offsetIndex = m_pBoard->screenToSegmentIndex(offsetPos);

	if(!mRotated)
		mRotDir = segIndex.x < offsetIndex.x ? 1 : -1;*/
}

void RotateRound::ProcessMessage( SFMessage* msg )
{
	ClientMessage* cmsg = dynamic_cast<ClientMessage*>(msg);

	SFMath::Vector2Di mousePos = SFMath::Vector2Di(cmsg->x,cmsg->y);

	mRotIndicatorPos = mousePos;

	SFMath::Vector2Di segIndex = m_pBoard->screenToSegmentIndex(mousePos);
	SFMath::Vector2Di offsetPos = SFMath::Vector2Di(mousePos.x + m_pBoard->getSegmentWidthInPixles()/2,mousePos.y);
	SFMath::Vector2Di offsetIndex = m_pBoard->screenToSegmentIndex(offsetPos);

	if(!mRotated)
		mRotDir = segIndex.x < offsetIndex.x ? 1 : -1;

	if(!mRotated)
	{
		SFMath::Vector2Di pos(mousePos.x,mousePos.y);
		sStone stone = sStone(sStone::EMPTY);

		if(m_pBoard->isValidSegmentRotation(pos))
		{
			mToRotate = m_pBoard->createSurfaceToRotate(m_pBoard->screenToSegmentIndex(pos));
			mRotated = true;

			SFMath::Vector2Di segIndex = m_pBoard->screenToSegmentIndex(pos);
			SFMath::Vector2Di offsetPos = SFMath::Vector2Di(pos.x + m_pBoard->getSegmentWidthInPixles()/2,pos.y);
			SFMath::Vector2Di offsetIndex = m_pBoard->screenToSegmentIndex(offsetPos);

			mRotDir = segIndex.x < offsetIndex.x ? 1 : -1;
			mRotOrigin->x = m_pBoard->segmentToScreenIndex(segIndex).x;
			mRotOrigin->y = m_pBoard->segmentToScreenIndex(segIndex).y;
			m_pBoard->setSegmentRenderStatus(pos,false);

			bool clockwise = mRotDir == 1;
			m_pBoard->rotateSegmentAt(pos, clockwise);
		}
	}
}


