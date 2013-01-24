#pragma once
#include "GameState.h"
#include "SDL.h"
#include "ClientBase.h"

class PentagoBase;

class JoinServerState : public GameState
{
public:
	JoinServerState(PentagoBase* base);
	~JoinServerState(void);

	virtual void OnEnter();
	virtual void Update(const float& time);
	virtual void Render(SDL_Surface* gs);

protected:
	ClientBase* mClient;
	bool mConnected;

};

