#pragma once

#include "IMouseListener.h"
#include "IkeyboardListener.h"

#include <vector>
#include "Vector2D.h"
class KeyEvent;

class SFMouse
{
public:
	static SFMouse *CreateMouse(int* px, int* py)
	{
		return new SFMouse(px,py);
	}

	void RemoveMouse(SFMouse* mouse)
	{
		delete mouse;
	}

	const int X() const {return *m_pX;}
	const int Y() const {return *m_pY;}
	const float* DistX() const {return &mDistX;}
	const float* DistY() const {return &mDistY;}
	const bool LeftButton() const {return mLeftButton;}
	const bool RightButton() const {return mRightButton;}

	void SetDistanceSinceLastFrame(const float& x,const float& y)
	{
		mDistX = x; mDistY = y;
	}

	void SetLeftMouseButton(bool down)
	{
		mLeftButton = down;
	}

	void SetRightMouseButton(bool down)
	{
		mRightButton = down;
	}

	const bool Drag() const
	{
		return mDrag;
	}
	void SetDrag(bool b)
	{
		mDrag = b;
	}


protected:
	int* m_pX;
	int* m_pY;

	float mDistX, mDistY;
	bool mLeftButton, mRightButton;
	bool mDrag;
	SFMouse(int* mx, int* my)
	{
		m_pX = mx;
		m_pY = my;

		mDistX = 0; mDistY = 0;
		mLeftButton = false; mRightButton = false;
		mDrag = false;
	}

	~SFMouse()
	{
		m_pX = NULL;
		m_pY = NULL;
	}
};

class InputManager
{

public:
	InputManager(void);
	~InputManager(void);

	void AddMouseListener(IMouseListener* listener);
	void AddKeyboardListener(IKeyboardListener* listener);

	void RemoveMouseListener(IMouseListener* listener);
	void RemoveKeyboardListener(IKeyboardListener* listener);

	void ProcessInput(KeyEvent& evt);

	bool IsKeyDown(KeyEvent& key);
	bool IsKeyDown(char c);

	const std::string GetInputCharacter(KeyEvent& evt);

	const int& MouseX() const
	{
		return mMouseX;
	}

	const int& MouseY() const
	{
		return mMouseY;
	}
	SFMath::Vector2Df GetMouseXY()
	{
		float x = static_cast<float>(mMouse->X());
		float y = static_cast<float>(mMouse->Y());
		return SFMath::Vector2Df(x,y);
	}


private:
	void UpdateMouseSinceLastFrame(KeyEvent& evt);
	void UpdateKeyboardSinceLastFrame(KeyEvent& evt);
	void ProcessKeyDown(KeyEvent& evt, IKeyboardListener* listener);
	void ProcessMouseDown(KeyEvent& evt, IMouseListener* listener);
	void ProcessMouseReleased(KeyEvent& evt, IMouseListener* listener);
	void ProcessMouseMotion(KeyEvent& evt, IMouseListener* listener);
	void ProcessMouseClicked(KeyEvent& evt, IMouseListener* listener);
	void ProcessMouseDrag(KeyEvent& evt, IMouseListener* listener);
	void ProcessMouseOver(KeyEvent& evt, IMouseListener* listener);
	void ProcessMouseMove(KeyEvent& evt, IMouseListener* listener);

	std::vector<IMouseListener*> mMouseListeners;
	std::vector<IKeyboardListener*> mKeyListeners;

	int* mKeysDown;

	int mMouseX, mMouseY;
	int mMouseLastX, mMouseLastY;
	SFMouse* mMouse;

	bool mLBLastState;
	bool mLBState;
	char mLastKeyDown;

	typedef std::vector<IMouseListener*>::iterator MouseListenerIter;
	typedef std::vector<IKeyboardListener*>::iterator KeyListenerIter;

};

