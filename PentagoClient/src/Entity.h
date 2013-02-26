#pragma once

#include "irenderable.h"
#include "IMouseListener.h"
#include "Vector2D.h"

class Entity :
	public IRenderable, public IMouseListener
{
public:
	Entity()
	{
	}
	
	Entity(const int& id);
	virtual ~Entity(void);

	void setPosition(SFMath::Vector2Di pos)
	{mPosition = pos;}

	virtual void Render(SDL_Surface* screen);
	virtual int GetLayer() {return 0;}

	virtual void OnClicked(const SFMouse* mouse);
	virtual void OnMouseOver(const SFMouse* mouse);
	virtual void OnMouseDown(const SFMouse* mouse);
	virtual void OnMouseReleased(const SFMouse* mouse);
	virtual void OnMouseMove(const SFMouse* mouse);
	virtual void OnMouseDrag(const SFMouse* mouse);

	virtual bool CheckMouseOver(const SFMouse* mouse);

	virtual const int& MouseListenerId() {return mEntityID;}
	virtual const int& ListenerPriority() {return mEntityID;}

	SFMath::Vector2Di Position()
	{return mPosition;}
protected:

	SFMath::Vector2Di mPosition;
	std::string mEntityStrID;
	int mEntityID;
};
