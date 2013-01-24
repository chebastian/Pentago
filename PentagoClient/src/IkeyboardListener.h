#pragma once

#include <string>
class KeyEvent;

class IKeyboardListener
{
public:
	virtual void OnKeyClicked(KeyEvent& evt) = 0;
	virtual void OnKeyDown(KeyEvent& evt) = 0;
	virtual void OnKeyUp(KeyEvent& evt) = 0;

	virtual const int& KeyListenerId() = 0;
};