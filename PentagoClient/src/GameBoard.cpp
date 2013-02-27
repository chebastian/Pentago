#include "GameBoard.h"
#include <iostream>
#include <random>
#include <Windows.h>

GameBoard::GameBoard(void)
{
	mWidthInStones = 6;
	mHeightInStones = 6;
	mStoneSqSz =32;
	mWidth = mWidthInStones * mStoneSqSz;
	mHeight = mHeightInStones * mStoneSqSz;
	mHightlightedIndex = SFMath::Vector2Di();
	mSegmentWidth = 3; mSegmentHeight = 3;
	mRotateingSegmentIndex = SFMath::Vector2Di(-1,-1);
	mScreenRenderPosition = SFMath::Vector2Di(200,100);
	initGraphics();
}

GameBoard::~GameBoard(void)
{
}

void GameBoard::initGraphics()
{
	mBoardSprite = SDL_LoadBMP("../../media/textures/stones.bmp");
	mBoardSprite = mBoardSprite;

	
	mSprEmpty = SDLWrapper::GetInstance()->createNewSubSurface(mBoardSprite,
		getSrcRectOfStone(sStone(sStone::EMPTY)));

	mSprP1 = SDLWrapper::GetInstance()->createNewSubSurface(mBoardSprite,
		getSrcRectOfStone(sStone(sStone::P1)));

	mSprP2 = SDLWrapper::GetInstance()->createNewSubSurface(mBoardSprite,
		getSrcRectOfStone(sStone(sStone::P2)));
}

void GameBoard::initBoard()
{
	mField = Field();

	for(int x = 0; x < mWidthInStones; x++)
	{
		mField.push_back(Stones());
		for(int y = 0; y < mHeightInStones; y++)
		{
			mField.at(x).push_back(sStone(sStone::EMPTY));
		}
	}
} 

sStone GameBoard::getStoneAtIndex(SFMath::Vector2Di index)
{
	sStone s = sStone(sStone::EMPTY);
	try
	{
		s = mField.at(index.x).at(index.y);
	}
	catch(std::exception& e)
	{
		s.value = sStone::NOT_CREATED;
		e.what();
	}

	return s;
}

void GameBoard::Render(SDL_Surface* gs)
{
	for(int y = 0; y < mHeightInStones; y++)
	{
		for(int x = 0; x < mWidthInStones; x++)
		{
			SFMath::Vector2Di idx = SFMath::Vector2Di(x,y);
			RenderStone(gs,getStoneAtIndex(idx),idx);
		}
	}
}

void GameBoard::RenderStone(SDL_Surface* gs, const sStone& s, const SFMath::Vector2Di& pos)
{
	SDL_Rect rect = SDL_Rect();
	
	rect.x = (Sint16)((pos.x * mStoneSqSz) + mScreenRenderPosition.x);
	rect.y = (Sint16)((pos.y * mStoneSqSz) + mScreenRenderPosition.y);
	rect.w = (Uint16)(mStoneSqSz)-1;
	rect.h = (Uint16)(mStoneSqSz)-1;

	SFMath::Vector2Di segIndex = screenToSegmentIndex(SFMath::Vector2Di(rect.x,rect.y));
	bool isInDisabledSegmenet = segIndex.x == mRotateingSegmentIndex.x &&
		segIndex.y == mRotateingSegmentIndex.y;
	
	if(isInDisabledSegmenet)
	{
		return;
	}

	SDL_Rect srcRect = getSrcRectOfStone(s);
	SDL_BlitSurface(mBoardSprite,&srcRect,gs,&rect);
}

SDL_Rect GameBoard::getSrcRectOfStone(sStone s)
{
	Sint16 sw = (Sint16)mStoneSqSz;
	Sint16 sh = (Sint16)mStoneSqSz;
	SDL_Rect rect;
	rect.x = (Sint16)(s.value * sw);
	rect.y = 0;
	rect.w = sw;
	rect.h = sh;

	return rect;
}

SFMath::Vector2Di GameBoard::screenToBoardIndex(SFMath::Vector2Di pos)
{
	SFMath::Vector2Di res = SFMath::Vector2Di();

	res.x = (pos.x - mScreenRenderPosition.x)/ mStoneSqSz;
	res.y = (pos.y - mScreenRenderPosition.y) / mStoneSqSz;

	return res;
}

SFMath::Vector2Di GameBoard::screenToSegmentIndex(const SFMath::Vector2Di& pos)
{
	unsigned int indexX = (pos.x - mScreenRenderPosition.x)/ (mSegmentWidth*mStoneSqSz);
	unsigned int indexY = (pos.y -mScreenRenderPosition.y) / (mSegmentHeight*mStoneSqSz);
	return SFMath::Vector2Di(indexX, indexY);
}

SFMath::Vector2Di GameBoard::segmentToScreenIndex(const SFMath::Vector2Di& segIndex)
{
	SFMath::Vector2Di screenPos = SFMath::Vector2Di(0,0);
	screenPos.x = ((segIndex.x * mSegmentWidth)*mStoneSqSz)+mScreenRenderPosition.x;
	screenPos.y = ((segIndex.y * mSegmentHeight)*mStoneSqSz)+mScreenRenderPosition.y;

	return screenPos;
}

SFMath::Vector2Di GameBoard::stoneIndexToScreen(const SFMath::Vector2Di& index)
{
	SFMath::Vector2Di screenPos = SFMath::Vector2Di(0,0);
	screenPos.x = (index.x * mStoneSqSz)+mScreenRenderPosition.x;
	screenPos.y = (index.y * mStoneSqSz)+mScreenRenderPosition.y;

	return screenPos;
}


void GameBoard::highLightStoneAtScreenIndex(const SFMath::Vector2Di& pos)
{
	SFMath::Vector2Di idx = screenToBoardIndex(pos);
	mHightlightedIndex = idx;
}

void GameBoard::setStoneAttScreenIndex(sStone s, const SFMath::Vector2Di& pos)
{
	SFMath::Vector2Di indexPos = screenToBoardIndex(pos);
	setStoneAtIndex(s,indexPos);
}

void GameBoard::setStoneAtIndex(sStone s, const SFMath::Vector2Di& index)
{
	try
	{
		mField.at(index.x).at(index.y) = s;
	}
	catch(std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}

void GameBoard::rotateSegmentAt(const SFMath::Vector2Di& pos, bool clockwise)
{
	SFMath::Vector2Di indexPos = screenToSegmentIndex(pos);

	GameBoard::Field seg = getSegmentAtIndex(indexPos);

	for(size_t x = 0; x < seg.size(); x++)
	{
		for(size_t y = 0; y < seg.at(x).size(); y++)
		{
			int xindex = (seg.size()-1)-x;
			int yindex = y;
			
			if(clockwise)
			{
				xindex = x;
				yindex = (seg.at(x).size()-1)-y;
			}

			sStone s1 = seg.at(xindex).at(yindex);
			SFMath::Vector2Di boardIndex(y + (indexPos.x*mSegmentWidth),x + (indexPos.y * mSegmentHeight));
			setStoneAtIndex(s1,boardIndex);
		}
	}
}

GameBoard::Field GameBoard::getSegmentAtIndex(const SFMath::Vector2Di& index)
{
	GameBoard::Field f = GameBoard::Field();

	for(int i = 0; i < mSegmentWidth; i++)
	{
		f.push_back(Stones());
		for(int j = 0; j < mSegmentWidth; j++)
		{
			SFMath::Vector2Di ix(i,j);
			ix.x += (index.x * mSegmentWidth);
			ix.y += (index.y * mSegmentHeight);

			sStone s = getStoneAtIndex(ix);
			f.at(i).push_back(s);
		}
	}

	return f;
}

bool GameBoard::playerPlaceStoneAtScreenPos(const SFMath::Vector2Di& pos, sStone s)
{
	SFMath::Vector2Di index = screenToBoardIndex(pos);
	if(isValidStonePlacement(index))
	{
		setStoneAtIndex(s,index);
		return true;
	}

	return false;
}

bool GameBoard::isValidStonePlacement(const SFMath::Vector2Di& boardIndex)
{
	sStone currentStone = getStoneAtIndex(boardIndex);
	bool valid = true;
	bool invalid = false;
	bool isValidPlacement = currentStone.value == sStone::EMPTY ? valid : invalid;

	return isValidPlacement;
}

bool GameBoard::isValidSegmentRotation(const SFMath::Vector2Di& screenPos)
{
	SFMath::Vector2Di segIndex = screenToSegmentIndex(screenPos);
	return segmentHasStones(segIndex);
}

SDL_Surface* GameBoard::createSurfaceToRotate(const SFMath::Vector2Di& index)
{
	SDL_Surface* segmentSurface;
	GameBoard::Field f = getSegmentAtIndex(index);

	int segmentWidthInPixels = mSegmentWidth * mStoneSqSz;
	int segmentHeightInPixels = mSegmentHeight * mStoneSqSz;

	segmentSurface = SDL_CreateRGBSurface(SDL_HWSURFACE,segmentWidthInPixels,
		segmentHeightInPixels,32,0,0,0,255);

	int segmentOffsetX = index.x * mSegmentWidth;
	int segmentOffsetY = index.y * mSegmentHeight;

	for(int y = 0; y < mSegmentHeight; y++)
	{
		for(int x = 0; x < mSegmentWidth; x++)
		{
			sStone s = getStoneAtIndex(SFMath::Vector2Di(x+segmentOffsetX,y+segmentOffsetY));//f.at(x + segmentOffsetX).at(y+segmentOffsetY).value;
			SDL_Surface* src = getSurfaceOfStoneType(s.value);

			/*SDLWrapper::GetInstance()->pasteSurfaceIntoSurface(segmentSurface,src,
				SFMath::Vector2Di(segmentOffsetX+(x*mStoneSqSz),
				segmentOffsetY+(y*mStoneSqSz)));*/
			SDLWrapper::GetInstance()->pasteSurfaceIntoSurface(segmentSurface,src,
				SFMath::Vector2Di((x*mStoneSqSz),
				(y*mStoneSqSz)));
		}
	}

	return segmentSurface;
}

void GameBoard::setSegmentRenderStatus(const SFMath::Vector2Di& screenPos,bool status)
{
	if(status == false)
	{
		mRotateingSegmentIndex = screenToSegmentIndex(screenPos);
	}
	else
	{
		mRotateingSegmentIndex.x = -1;
		mRotateingSegmentIndex.y = -1;
	}
}

SDL_Surface* GameBoard::getSurfaceOfStoneType(sStone::Type type)
{
	SDL_Surface* returnSurface = mBoardSprite;
	if(type == sStone::EMPTY)
	{
		returnSurface = mSprEmpty;
	}
	else if(type == sStone::P1)
	{
		returnSurface = mSprP1;
	}
	else if(type == sStone::P2)
	{
		returnSurface = mSprP2;
	}

	return returnSurface;
}

void GameBoard::resetBoard()
{
	this->initBoard();
}

int GameBoard::getMaxStonesInRow(sStone::Type type)
{
	int curMaxX = 0;
	int maxX = 0; 

	for(int i = 0; i < mHeightInStones; i++)
	{
		curMaxX = 0;
		for(int j = 0; j < mWidthInStones; j++)
		{
			sStone s = getStoneAtIndex(SFMath::Vector2Di(j,i));
			if(s.value == type)
			{
				curMaxX++;
			}
			else
			{
				if(curMaxX > maxX)
					maxX = curMaxX;

				curMaxX = 0;
			}
		}
		if(curMaxX> maxX)
			maxX = curMaxX;
	}

	return maxX;
}

int GameBoard::getMaxStonesInCol(sStone::Type type)
{
	int curMaxX = 0;
	int maxX = 0; 

	for(int i = 0; i < mWidthInStones; i++)
	{
		for(int j = 0; j < mHeightInStones; j++)
		{
			sStone s = getStoneAtIndex(SFMath::Vector2Di(i,j));
			if(s.value == type)
			{
				curMaxX++;
			}
			else
			{
				if(curMaxX > maxX)
					maxX = curMaxX;

				curMaxX = 0;
			}
		}
		if(curMaxX > maxX)
			maxX = curMaxX;

		curMaxX = 0;
	}

	return maxX;
}

int GameBoard::getMaxStonesInDir(const SFMath::Vector2Di& dir, sStone::Type type)
{
	int currentMaximum = 0;
	int smax = 0;

	SFMath::Vector2Di idx(0,0);
	for(int y = 0; y < mHeightInStones; y++)
	{
		currentMaximum =  0;
		for(int x = 0; x < mWidthInStones; x++)
		{
			currentMaximum =  0;
			while(	idx.x >= 0 && idx.x < mWidthInStones &&
				idx.y >= 0 && idx.y < mHeightInStones)
			{
				sStone s = getStoneAtIndex(idx);
				if(s.value == type)
				{
					currentMaximum++;
				}
				else
				{
					if(smax < currentMaximum)
						smax = currentMaximum;

					currentMaximum = 0;
				}
				idx += dir;
			}
			if(currentMaximum > smax)
				smax = currentMaximum;

			idx.x = x;//+dir.x;
			idx.y = y;//+dir.y;

		}
	}

	return smax;
}

bool GameBoard::segmentHasStones(const SFMath::Vector2Di& segmentIndex)
{
	GameBoard::Field segment = getSegmentAtIndex(segmentIndex);

	try
	{
		for(int y = 0; y < mSegmentHeight; y++)
		{
			for(int x = 0; x < mSegmentWidth; x++)
			{
				bool isStone = segment.at(x).at(y).value != sStone::EMPTY &&
					segment.at(x).at(y).value != sStone::NOT_CREATED;

				if(isStone)
					return true;
			}
		}
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "Exception in segment has stones" << std::endl;

	}

	return false;
}

void GameBoard::SetRandomStoneInBoard(sStone s)
{
	int x = rand()%mWidthInStones;
	int y = rand()%mHeightInStones;
	while(getStoneAtIndex(SFMath::Vector2Di(x,y)).value != sStone::EMPTY)
	{
		x = rand()%mWidthInStones;
		y = rand()%mHeightInStones;
	}
	setStoneAtIndex(s,SFMath::Vector2Di(x,y));
}

int GameBoard::getSegmentWidthInPixles()
{
	return mSegmentWidth*mStoneSqSz;
}