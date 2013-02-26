#pragma once
#include "Vector2D.h"
#include <vector>
#include "SDLWrapper.h"
#include <exception>

struct sStone
{
	enum Type
	{
		EMPTY,
		P1,
		P2,
		HIGHLIGHTED,
		NOT_CREATED
	};

	sStone(Type val)
	{
		value = val;
	}

	Type value;
};

class GameBoard
{
public:
	GameBoard(void);
	virtual ~GameBoard(void);

	void initBoard();
	void Render(SDL_Surface* gs);

	SFMath::Vector2Di screenToBoardIndex(SFMath::Vector2Di pos);
	SFMath::Vector2Di screenToSegmentIndex(const SFMath::Vector2Di& pos);
	SFMath::Vector2Di segmentToScreenIndex(const SFMath::Vector2Di& segIndex);
	SFMath::Vector2Di stoneIndexToScreen(const SFMath::Vector2Di& index);
	sStone getStoneAtIndex(SFMath::Vector2Di index);

	void highLightStoneAtScreenIndex(const SFMath::Vector2Di& pos);
	void setStoneAttScreenIndex(sStone s, const SFMath::Vector2Di& pos);
	void setStoneAtIndex(sStone s, const SFMath::Vector2Di& index);
	void rotateSegmentAt(const SFMath::Vector2Di& pos, bool clockwise);

	int getMaxStonesInRow(sStone::Type type);
	int getMaxStonesInCol(sStone::Type type);
	int getMaxStonesInDir(const SFMath::Vector2Di& dir,sStone::Type type);
	int getSegmentWidthInPixles();

	bool playerPlaceStoneAtScreenPos(const SFMath::Vector2Di& pos, sStone s);
	bool isValidStonePlacement(const SFMath::Vector2Di& boardIndex);
	bool isValidSegmentRotation(const SFMath::Vector2Di& screenPos);

	SDL_Surface* createSurfaceToRotate(const SFMath::Vector2Di& index);

	void setSegmentRenderStatus(const SFMath::Vector2Di& segmentIndex, bool status);
	void setPosition(const SFMath::Vector2Di& pos)
	{mScreenRenderPosition = pos;}


	void resetBoard();
	void SetRandomStoneInBoard(sStone s);


	int getBoardWidth() {return mWidthInStones;}
	int getBoardHeight() {return mHeightInStones;}
protected:

	void initGraphics();
	SDL_Rect getSrcRectOfStone(sStone s);
	typedef std::vector<sStone> Stones;
	typedef std::vector<Stones> Field;

	bool segmentHasStones(const SFMath::Vector2Di& segmentIndex);
	void RenderStone(SDL_Surface* gs, const sStone& s, const SFMath::Vector2Di& pos);

	Field getSegmentAtIndex(const SFMath::Vector2Di& index);
	SDL_Surface* getSurfaceOfStoneType(sStone::Type type);

	int mWidth, mHeight;
	int mStoneSqSz;
	int mWidthInStones;
	int mHeightInStones;
	int mSegmentWidth;
	int mSegmentHeight;

	Field mField;
	SFMath::Vector2Di mHightlightedIndex;
	SFMath::Vector2Di mRotateingSegmentIndex;
	SFMath::Vector2Di mScreenRenderPosition;

	SDL_Surface* mBoardSprite;
	SDL_Surface* mSprEmpty;
	SDL_Surface* mSprP1;
	SDL_Surface* mSprP2;
};