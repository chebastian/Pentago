#pragma once
#include "boardactor.h"
#include "IMouseListener.h"

#pragma warning( disable : 4100 )

class HumanPlayer :
	public BoardActor, public IMouseListener
{
public:
	HumanPlayer(PentagoBase* base,GameBoard* board);
	virtual ~HumanPlayer(void);
	
	virtual void start();
	virtual void end();

	virtual void OnClicked(const SFMouse* mouse);
	virtual void OnMouseOver(const SFMouse* mouse);
	virtual void OnMouseDown(const SFMouse* mouse);
	virtual void OnMouseReleased(const SFMouse* mouse);
	virtual void OnMouseMove(const SFMouse* mouse);
	virtual void OnMouseDrag(const SFMouse* mouse);

	virtual bool CheckMouseOver(const SFMouse* mouse){return true;}

	virtual const int& MouseListenerId() {return mID;}
	virtual const int& ListenerPriority(){return mID;}

protected:
	int mID;

};

