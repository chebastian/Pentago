#pragma once
#include <Windows.h>

class Runnable
{
public:
	Runnable(void)
	{

	}

	virtual ~Runnable(void)
	{
	}

	static DWORD WINAPI run_thread(LPVOID args)
	{
		Runnable* r = static_cast<Runnable*>(args);
		return r->run();
	}

protected:
	virtual DWORD run() = 0;

};

