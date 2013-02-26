#include "Board.h"
#include <exception>
#include <iostream>
#include "SDLWrapper.h"
#include <sstream>

Board::Board()
	:Entity(BOARD_ID)
{
	mField = Segments();
	this->mStonesInSegment = 3;
	mStoneSz = SFMath::Point2D<int>(32,32);
	this->mNumSegmentsX = 3;
	mRenderPos = SFMath::Vector2Di(0,0);
	testPos = SFMath::Vector2Di();
	createEmptyBoard(mNumSegmentsX,mNumSegmentsX);

	mSegmentSz = mStonesInSegment * mStoneSz.x;
}

Board::~Board()
{
}

void Board::createEmptyBoard(int w, int h)
{
	mField.clear();
	for(int i = 0; i < w; i++)
	{
		for(int j = 0; j < h; j++)
		{
			BoardSegment seg =BoardSegment::emptySegment(mStonesInSegment,mStonesInSegment); 
			seg.randomizeSegment();
			seg.id = j+i*w;
			seg.index.x = j;
			seg.index.y = i;
			mField.push_back( seg );
		}
	}
}

void Board::addStoneToBoard(Stone s, SFMath::Vector2Di pos)
{
	try
	{
		s = 0;
		int seg = screenTosegmentIndex(pos);
		getStoneInSegment(seg, screenToIndexInSegment(seg,pos));
	}
	catch(std::exception e)
	{
		std::cout << e.what();
	}
}

int Board::screenTosegmentIndex(SFMath::Vector2Di pos)
{
	SFMath::Vector2Di res(pos.x - mRenderPos.x,pos.y - mRenderPos.y);
	res.x /= mSegmentSz;
	res.y /= mSegmentSz;

	unsigned int val = res.x + res.y * mNumSegmentsX;
	if(val > mField.size())
		val = 0;
	return val;
}

SFMath::Vector2Di Board::screenToIndexInSegment(int seg, SFMath::Vector2Di pos)
{
	SFMath::Vector2Di res(pos.x - mRenderPos.x,pos.y - mRenderPos.y);


	if(res.x == 0 || res.y == 0 || seg < 0)
		return res;

	res.x /= (mStoneSz.x + (getSegment(seg).index.x*mSegmentSz));
	res.y /= (mStoneSz.y + (getSegment(seg).index.y*mSegmentSz));

	return res;
}
Stone Board::getStoneInSegment(int seg, SFMath::Vector2Di pos)
{
	Stone s = EMPTY_STONE;
	SFMath::Vector2Di segmentIndex = screenToIndexInSegment(seg,pos);
	
	s = mField.at(seg).segment.at(segmentIndex.x).at(segmentIndex.y);
	return s;
}

int Board::toOneDimensionalIndex(SFMath::Vector2Di index)
{
	return index.x + index.y * mStonesInSegment;
}

void Board::rotateSegment(int id)
{
	BoardSegment seg = this->getSegment(id);
}

BoardSegment Board::getSegment(int id)
{
	BoardSegment seg;

	try
	{
		seg = this->mField.at(id);
	}
	catch(std::exception& e)
	{
		std::cout << e.what();
	}

	return seg;
}

void Board::Render(SDL_Surface* gs)
{
	SFMath::Point2D<int> pos = mRenderPos;
	int counter = 0;
	
	for(size_t i = 0; i < mField.size();i++)
	{
		RenderSegment(gs,pos,getSegment(i));
		pos.x += mStoneSz.x * getSegment(i).width;
		counter++;
		
		if(counter >= this->mNumSegmentsX)
		{
			pos.x = mRenderPos.x;
			pos.y += mStoneSz.y * getSegment(i).height;

			counter = 0;
		}
	}
}

void Board::RenderSegment(SDL_Surface* screen,SFMath::Point2D<int> pos, BoardSegment segment)
{
	SDL_Rect rect = SDL_Rect();

	rect.w = (Uint16)mStoneSz.x;
	rect.h = (Uint16)mStoneSz.y;

	for(size_t i = 0; i < segment.segment.size(); i++)
	{
		for(size_t j = 0; j < segment.segment.at(i).size(); j++)
		{
			rect.x = (Uint16)(pos.x + i * mStoneSz.x);
			rect.y = (Uint16)(pos.y + j * mStoneSz.y);

			int color = 0xFF0000;
			if(segment.segment.at(i).at(j) == 0)
				color = 0x555555;
			else if(segment.segment.at(i).at(j) == 1)
				color = 0xAAAAAA;
			else
				color = 0xAAAAAA;

			SDL_FillRect(screen,&rect,color);

			if((int)i == testPos.x && (int)j == testPos.y && segment.id == testSeg)
				SDL_FillRect(screen,&rect,0xFAFA00);

			std::string k = "";
			std::stringstream ss;
			ss << testSeg << " "<< testPos.x << " "<< " " << testPos.y;
			k = ss.str();

			SDLWrapper::GetInstance()->RenderString(k,10,10);

		}
	}
}

void Board::highlightStoneAtPos(SFMath::Vector2Di pos)
{
	SFMath::Vector2Di offsetPos = pos - mRenderPos;

	int seg = screenTosegmentIndex(pos);
	SFMath::Vector2Di p = screenToIndexInSegment(seg,offsetPos);
	testPos = p;
	testSeg = seg;
}