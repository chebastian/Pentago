#pragma once
#include "gameround.h"
class RotateRound :
	public GameRound
{
public:
	RotateRound(PentagoBase* base, GameBoard* board,const PLAYER_ID playerID);
	virtual ~RotateRound(void);

	RotateRound(RotateRound&& other)
		:GameRound(other)
	{
		std::cout << "Move called on gameround" << std::endl;
	}

	virtual void OnUpdate(const float& time);
	virtual void OnEnter();
	virtual void OnRender(SDL_Surface* gs);
	virtual void OnExit();
	virtual void OnMouseDown(const SFMouse* mouse);
	virtual void OnMouseMove(const SFMouse* mouse);

	virtual void ProcessMessage(SFMessage* msg);

protected:


	void RenderRotatedSegment(SDL_Surface* gs);
		void RenderRotationIndicator(const SFMath::Vector2Di& pos,SDL_Surface* gs);
	void updateRotation(const float& time);
	void rotateSegment();

	bool mRotated;
	SDL_Surface* mToRotate;
	float mCurrRot;
	float mRotationDelta;
	int mRotDir;
	SFMath::Vector2Di* mRotOrigin;
	SFMath::Vector2Di mRotIndicatorPos;
};

