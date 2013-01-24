#pragma once

 enum Event_Type
	{
		EVT_KEYDOWN,
		EVT_KEYRELEASED,
		EVT_MOUSEMOTION,
		EVT_MOUSEPRESSED,
		EVT_MOUSEDRAG,
		EVT_MOUSERELEASED,
		EVT_NONE,
		NUM_EVENTS
	};

 enum Key_Code
 {
	 KC_SPACE,
	 KC_BACKSPACE,
	 KC_ESC,
	 KC_LEFT,
	 KC_RIGHT,
	 KC_UP,
	 KC_DOWN,
	 KC_SHIFT,
	 KC_NONE,
	 NUM_KC
 };

class KeyEvent
{
public:
	

	KeyEvent()
	{
		Type = NUM_EVENTS;
		keyChar = ' ';
		mouseX = 0; mouseY = 0;
		motionX = 0; motionY = 0;
		KeyCode = Key_Code::KC_NONE;
	}

	KeyEvent(Event_Type type)
	{
		Type = type;
		keyChar = ' ';
		mouseX = 0; mouseY = 0;
		motionX = 0; motionY = 0;
		KeyCode = Key_Code::KC_NONE;
	}

	Event_Type Type;
	Key_Code KeyCode;
	char keyChar;
	int mouseX, mouseY;
	int motionX, motionY;
};