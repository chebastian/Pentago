#pragma once
#include "Entity.h"
#include <vector>
#include <random>

typedef Uint8 Stone;
typedef std::vector<Stone> Row;
typedef std::vector<Row> Field;


class BoardSegment{
	public:
		BoardSegment()
		{
			segment = Field();
			width = 0; height = 0;
			id = 0;
			index = SFMath::Vector2Di();
		}

		BoardSegment(const BoardSegment& seg)
		{
			segment = seg.segment;
			width = seg.width;
			height = seg.height;
			id = seg.id;
			index = seg.index;
		}

	public:
		Field segment;
		int width, height;
		SFMath::Vector2Di index;
		int id;

		static BoardSegment emptySegment(int w, int h)
		{

			BoardSegment seg = BoardSegment();
			seg.width = w;
			seg.height = h;
			seg.index = SFMath::Vector2Di();
			for(int i = 0; i < w; i++)
			{
				seg.segment.push_back(Row());
				for(int j = 0; j < h; j++)
				{
					seg.segment.at(i).push_back(0);
				}
			}

			return seg;
		}


		void randomizeSegment()
		{
			for(int i = 0; i < width; i++)
			{
				for(int j = 0; j < height; j++)
				{
					segment.at(i).at(j) = rand()%3;
				}
			}
		}
	};

class Board : public Entity
{
public:
	Board();
	virtual ~Board();

	void addStoneToBoard(Stone s, SFMath::Vector2Di pos);
	void createEmptyBoard(int w, int h);
	void rotateSegment(int id);
	Stone getStoneInSegment(int seg, SFMath::Vector2Di pos);

	int screenTosegmentIndex(SFMath::Vector2Di pos);
	SFMath::Vector2Di screenToIndexInSegment(int seg, SFMath::Vector2Di pos);
	int toOneDimensionalIndex(SFMath::Vector2Di index);

	void Render(SDL_Surface* gs);

	void highlightStoneAtPos(SFMath::Vector2Di pos);
protected:

	void RenderSegment(SDL_Surface* screen, 
		SFMath::Point2D<int> pos, BoardSegment segment);

	BoardSegment getSegment(int id);
	
	static const int BOARD_ID = 1234;
	static const Stone EMPTY_STONE = 0;
	static const Stone RED_STONE = 1;
	static const Stone BLUE_STONE = 2;

	typedef std::vector<BoardSegment> Segments;
	Segments mField;
	int mStonesInSegment;
	int mNumSegmentsX;
	int mSegmentSz;
	SFMath::Point2D<int> mStoneSz;
	SFMath::Vector2Di mRenderPos;
	SFMath::Vector2Di testPos;
	int testSeg;
};