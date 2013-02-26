#include "AgentPlayer.h"
#include "PentagoBase.h"
#include <random>
#include "GameBoard.h"
#include "Vector2D.h"

AgentPlayer::AgentPlayer(PentagoBase* base,GameBoard* board)
	:BoardActor(base,board)
{
}


AgentPlayer::~AgentPlayer(void)
{
}

void AgentPlayer::update(const float& time)
{
	float delta = time;
	delta += delta;

	SFMath::Vector2Di index = getHighestValuedPointInBoard();
	
	ClientMessage msg(ClientMessage::TYPE_PLACED,mBoard->stoneIndexToScreen(index));
	SendClientMessage(&msg);
}

SFMath::Vector2Di AgentPlayer::getRandomScreenPos()
{
	SFMath::Vector2Di scpos;
	scpos.x = rand()%mGame->ScreenSize().x;
	scpos.y = rand()%mGame->ScreenSize().y;

	return scpos;
}

SFMath::Vector2Di AgentPlayer::getHighestValuedPointInBoard()
{
	SFMath::Vector2Di idx = SFMath::Vector2Di(0,0);

	int curMax = 0;
	//sStone::Type type = sStone::P1;
	SFMath::Vector2Di indexOfMax = SFMath::Vector2Di(0,0);
	for(int y = 0; y < mBoard->getBoardHeight(); y++)
	{
		for(int x = 0; x < mBoard->getBoardWidth(); x++)
		{
			idx.x = x;
			idx.y = y;

			//bool areOfSameType = mBoard->getStoneAtIndex(idx).value == type;
			//if(areOfSameType)
			{
				int value = getHighestValueOfIndex(idx);
				bool isOfHigherValue = value > curMax;
				if(isOfHigherValue && mBoard->isValidStonePlacement(idx))
				{
					curMax = value;
					indexOfMax = idx;
				}
			}
		}
	}

	if(curMax <= 0 || !mBoard->isValidStonePlacement(indexOfMax))
	{
		bool kyken = false;
		kyken = true;
	}

	return indexOfMax;
}

int AgentPlayer::getHighestValueOfIndex(const SFMath::Vector2Di& pos)
{
	int maxValue = 0;
	sStone stoneRef = mBoard->getStoneAtIndex(pos);

	std::vector<SFMath::Vector2Di> dirs;
	dirs.push_back(SFMath::Vector2Di(0,-1));
	dirs.push_back(SFMath::Vector2Di(1,0));
	dirs.push_back(SFMath::Vector2Di(0,1));
	dirs.push_back(SFMath::Vector2Di(-1,0));

	dirs.push_back(SFMath::Vector2Di(-1,-1));
	dirs.push_back(SFMath::Vector2Di(1,-1));
	dirs.push_back(SFMath::Vector2Di(1,1));
	dirs.push_back(SFMath::Vector2Di(-1,1));

	SFMath::Vector2Di currentIdx = pos;
	std::vector<SFMath::Vector2Di> found;

	bool isInBoard = (currentIdx.x > 0 && currentIdx.x < mBoard->getBoardWidth() &&
		currentIdx.y > 0 && currentIdx.y < mBoard->getBoardHeight());

	bool areOfEqualType = true;

	for(size_t dir = 0; dir < dirs.size(); dir++)
	{
		int numInDir = 0;
		currentIdx = dirs.at(dir) + pos;

		isInBoard = (currentIdx.x > 0 && currentIdx.x < mBoard->getBoardWidth() &&
		currentIdx.y > 0 && currentIdx.y < mBoard->getBoardHeight());

		areOfEqualType = mBoard->getStoneAtIndex(currentIdx).value == stoneRef.value;
		while(isInBoard && areOfEqualType)
		{
			areOfEqualType = mBoard->getStoneAtIndex(currentIdx).value == stoneRef.value;
			if(areOfEqualType)
			{
				currentIdx += dirs.at(dir);
				
				isInBoard = (currentIdx.x > 0 && currentIdx.x < mBoard->getBoardWidth() &&
					currentIdx.y > 0 && currentIdx.y < mBoard->getBoardHeight());

				numInDir++;
			}
		}

		maxValue = max(numInDir,maxValue);
	}


	return maxValue;
}

SFMath::Vector2Di AgentPlayer::getRandomEmptySpaceInBoard()
{
	SFMath::Vector2Di pos(0,0);

	return pos;
}

