#pragma once
#include "GameState.h"
#include "SDL.h"
#include "ClientBase.h"
#include "IkeyboardListener.h"
#include "KeyEvent.h"
#include "ChatClient.h"
#include <vector>

class PentagoBase;
class ClientPlayer;

class JoinServerState : public GameState, public IKeyboardListener
{
public:
	JoinServerState(PentagoBase* base);
	~JoinServerState(void);

	virtual void OnEnter();
	virtual void Update(const float& time);
	virtual void Render(SDL_Surface* gs);

	virtual void OnKeyClicked(KeyEvent& evt){};
	virtual void OnKeyDown(KeyEvent& evt);
	virtual void OnKeyUp(KeyEvent& evt){};

	virtual const int& KeyListenerId();

protected:
	ClientPlayer* mClient;

	bool mConnected;
	std::string mMsg;
};

