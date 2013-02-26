#include "InputManager.h"
#include <algorithm>
#include "KeyEvent.h"
#include <stdexcept>
#include <iostream>

#pragma warning( disable : 4100 )

InputManager::InputManager(void)
{
	mKeysDown = new int[256];

	for(int i = 0; i < 256; i++)
	{
		mKeysDown[i] = false;
	}

	mMouseX = 0;
	mMouseY = 0;
	mMouseLastX = 0;
	mMouseLastY = 0;
	mMouse = SFMouse::CreateMouse(&mMouseX, &mMouseY);
	mLBLastState = false;
	mLBState = true;
}


InputManager::~InputManager(void)
{
}

void InputManager::AddKeyboardListener(IKeyboardListener* listener)
{
	mKeyListeners.push_back(listener);
}

void InputManager::AddMouseListener(IMouseListener* listener)
{
	for(unsigned int i = 0; i < mMouseListeners.size(); i++)
	{
		if(mMouseListeners.at(i)->MouseListenerId() == listener->MouseListenerId())
		{
			std::cout << "CONFLICT IN MOUSE ID'S" << " WOND ADD LISTENER " << listener-> MouseListenerId() << std::endl;
			return;
		}
	}
	mMouseListeners.push_back(listener);
}

void InputManager::RemoveMouseListener(IMouseListener* listener)
{
	try
	{
		std::cout << listener->MouseListenerId() << std::endl;
		for(unsigned int i = 0; i < mMouseListeners.size(); i++)
		{
			if(mMouseListeners.at(i)->MouseListenerId() == listener->MouseListenerId())
			{
				std::cout << "Erasing: " << mMouseListeners.at(i)->MouseListenerId() << std::endl;
				mMouseListeners.erase(mMouseListeners.begin()+i);
				return;
			}
		}
		std::cout <<  "Dint find: " << listener->MouseListenerId() << std::endl;
	}
	catch(std::out_of_range e)
	{
		std::cout << e.what() << std::endl;
	}
}

void InputManager::RemoveKeyboardListener(IKeyboardListener* listener)
{
	for(unsigned int i = 0; i < mKeyListeners.size(); i++)
	{
		if(mKeyListeners[i]->KeyListenerId() == listener->KeyListenerId())
		{
			mKeyListeners.erase(mKeyListeners.begin() + i);
			return;
		}
	}
}

const std::string InputManager::GetInputCharacter(KeyEvent& evt)
{
	std::string character("");

	character = std::string(&evt.keyChar);
	return character;
}

bool InputManager::IsKeyDown(KeyEvent& key)
{
	return mKeysDown[key.keyChar] == 1;
}

bool InputManager::IsKeyDown(char c)
{
	return mKeysDown[c] == 1;
}

void InputManager::UpdateMouseSinceLastFrame(KeyEvent& evt)
{
	if(mMouse->LeftButton())
		mLBLastState = true;
	else
		mLBLastState = false;

	mMouse->SetDistanceSinceLastFrame(static_cast<float>(mMouseX - evt.mouseX), 
		static_cast<float>(mMouseY - evt.mouseY));
	if(evt.mouseX > 0 )
	{
		mMouseX = evt.mouseX;
		mMouseLastX = mMouseX;
	}

	if(evt.mouseY > 0)
	{
		mMouseY = evt.mouseY;
		mMouseLastY = mMouseY;
	}

	//mMouseLastX = mMouseX;
	//mMouseLastY = mMouseY;
}

void InputManager::ProcessInput(KeyEvent& evt)
{
	for(unsigned int i = 0; i < mMouseListeners.size(); i++)
	{
		IMouseListener* listener = mMouseListeners[i];
		ProcessMouseClicked(evt, listener);
		ProcessMouseDown(evt, listener);
		ProcessMouseDrag(evt, listener);
		ProcessMouseReleased(evt,listener);
		ProcessMouseMove(evt,listener);
		ProcessMouseOver(evt,listener);
	}

	for(unsigned int i = 0; i < mKeyListeners.size(); i++)
	{
		ProcessKeyDown(evt,mKeyListeners[i]);
	}

	UpdateMouseSinceLastFrame(evt);
	UpdateKeyboardSinceLastFrame(evt);

}

void InputManager::ProcessMouseOver(KeyEvent& evt, IMouseListener* listener)
{
	if(listener->CheckMouseOver(mMouse))
	{
		listener->OnMouseOver(mMouse);
	}
}

void InputManager::ProcessMouseMove(KeyEvent& evt, IMouseListener* listener)
{
	if(evt.mouseX > 0 && evt.mouseY > 0)
	{
		mMouseX = evt.mouseX;
		mMouseY = evt.mouseY;
	}
	listener->OnMouseMove(mMouse);
}

void InputManager::ProcessMouseDrag(KeyEvent& evt, IMouseListener* listener)
{
	if(evt.Type == Event_Type::EVT_MOUSEPRESSED)
	{
		mMouse->SetDistanceSinceLastFrame(float(evt.motionX), float(evt.motionY));
		if(!listener->CheckMouseOver(mMouse) || mMouse->Drag())
			return;

		if(mMouse->LeftButton() || mMouse->RightButton() && listener->CheckMouseOver(mMouse))
		{
			//mMouse->SetDrag(true);
			listener->OnMouseDrag(mMouse);
		}
	}
}


void InputManager::ProcessMouseClicked(KeyEvent& evt, IMouseListener* listener)
{
	if(evt.Type == Event_Type::EVT_MOUSEPRESSED)
	{
		mLBState = true;
		
		//if(evt.button.button == SDL_BUTTON_LEFT)
			mMouse->SetLeftMouseButton(true);
		//if(evt.button.button == SDL_BUTTON_RIGHT)
			mMouse->SetRightMouseButton(true);

		//listener->OnMouseDown(mMouse);

		if(!mLBLastState && listener->CheckMouseOver(mMouse))
		{
			listener->OnClicked(mMouse);
		}
	}
}

void InputManager::ProcessMouseReleased(KeyEvent& evt, IMouseListener* listener)
{
	if(evt.Type == Event_Type::EVT_MOUSERELEASED)
	{
		mLBState = false;
		mLBLastState = false;

		//if(evt.button.button == SDL_BUTTON_LEFT)
			mMouse->SetLeftMouseButton(false);
		//if(evt.button.button == SDL_BUTTON_RIGHT)
			mMouse->SetRightMouseButton(false);
		listener->OnMouseReleased(mMouse);
	}
}

void InputManager::ProcessKeyDown(KeyEvent& evt, IKeyboardListener* listener)
{

	bool keyDown = false;
	if(evt.Type == Event_Type::EVT_KEYDOWN)
	{
		if(!mKeysDown[evt.keyChar])
			listener->OnKeyClicked(evt);
		
		keyDown = true;
		listener->OnKeyDown(evt);
	}
	if(evt.Type == Event_Type::EVT_KEYRELEASED)
	{
		mKeysDown[evt.keyChar] = false;
		listener->OnKeyUp(evt);
	}

	/*
	bool keyDown = false;
	bool keyReleased = false;

	if(evt.type == SDL_KEYDOWN)
	{
		if(!mKeysDown[evt.key.keysym.sym])
			listener->OnKeyClicked(evt);

		//mKeysDown[evt.key.keysym.sym] = true;
		keyDown = true;
		//mLastKeyDown = evt.key.keysym.unicode;

		listener->OnKeyDown(evt);
	} 

	if(evt.type == SDL_KEYUP)
	{
		if(mKeysDown[evt.key.keysym.sym])
			keyReleased = true;

		mKeysDown[evt.key.keysym.sym] = false;
		mLastKeyDown = 'ws';

		listener->OnKeyUp(evt);
	}*/
}

void InputManager::UpdateKeyboardSinceLastFrame(KeyEvent& evt)
{
	if(evt.Type == Event_Type::EVT_KEYDOWN)
	{
		mKeysDown[evt.keyChar] = true;
		mLastKeyDown = evt.keyChar;
	}
	else if(evt.Type == Event_Type::EVT_KEYRELEASED)
	{
		mKeysDown[evt.keyChar] = false;
	}
}

void InputManager::ProcessMouseDown(KeyEvent& evt, IMouseListener* listener)
{
	if(evt.Type == Event_Type::EVT_MOUSEPRESSED)
		listener->OnMouseDown(mMouse);
}

