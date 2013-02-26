#pragma once
#include "boardactor.h"
#include "Vector2D.h"

class AgentPlayer :
	public BoardActor
{
public:
	AgentPlayer(PentagoBase* base,GameBoard* board);
	virtual ~AgentPlayer(void);

	virtual void update(const float& time);

protected:
	SFMath::Vector2Di getRandomScreenPos();
	SFMath::Vector2Di getHighestValuedPointInBoard();
	SFMath::Vector2Di getRandomEmptySpaceInBoard();
	int getHighestValueOfIndex(const SFMath::Vector2Di& index);
};

