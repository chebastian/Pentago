#pragma once
class IState
{
public:

	virtual void OnEnter() = 0;
	virtual void UpdateState(const float& time) = 0;
	virtual void OnExit() = 0;
};

