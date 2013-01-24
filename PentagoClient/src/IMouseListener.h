#pragma once

class SFMouse;
#include <string>

class IMouseListener
{
public:
	virtual void OnClicked(const SFMouse* mouse) = 0;
	virtual void OnMouseOver(const SFMouse* mouse) = 0;
	virtual void OnMouseDown(const SFMouse* mouse) = 0;
	virtual void OnMouseReleased(const SFMouse* mouse) = 0;
	virtual void OnMouseMove(const SFMouse* mouse) = 0;
	virtual void OnMouseDrag(const SFMouse* mouse) = 0;

	virtual bool CheckMouseOver(const SFMouse* mouse) = 0;	

	virtual const int& MouseListenerId() = 0;
	virtual const int& ListenerPriority() = 0;
};