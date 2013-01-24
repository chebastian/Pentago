#pragma once

#include "SDL.h"
#include "Entity.h"
#include "IRenderable.h"
#include "SDL_ttf.h"
#include "KeyEvent.h"
#undef main
#include <vector>

class InputManager;

typedef struct ColorRGB
{
	Uint8 r;
	Uint8 g;
	Uint8 b;

	ColorRGB(Uint8 red, Uint8 green, Uint8 blue)
		:r(red),g(green),b(blue)
	{}
} ColorRGB;

class SDLWrapper
{
public:

	static SDLWrapper* GetInstance()
	{
		static SDLWrapper instance;
		return &instance;
	}

	void Initialize();

	void InitOpelnGL();
	bool Update();
	void Render();

	void RenderString(const std::string& str, int x, int y, int incolor = 0xFFFFFF);
	float GetElapsedTime();
	const bool IsRunning() const {return mIsRunning;} 
	SDL_Surface* Screen() {return mScreen;}
	const float& ElapsedTime() {return mElapsedTime;}

	void DrawPixel(SDL_Surface* screen, int x, int y, ColorRGB* rgb);
	void GetKeysDown(int& keys);
	bool IsKeyDown(SDLKey key);
	void ClearInputBuffer();

	InputManager* GetInput()
	{
		return mInputMgr;
	}
	void ShutDown()
	{
		mIsRunning = false;
	}

	void ClearScreen();

private:

	void HandleInputFromSDL();
	Key_Code TranslateSDLKeyToKeyCodes(SDL_Event& evt);
	SDLWrapper(void);
	~SDLWrapper(void);


	bool mIsRunning;
	SDL_Surface* mScreen, mOffScreen;
	int* mKeysDown; 
	InputManager* mInputMgr;
	float mElapsedTime;
	TTF_Font* mFontTTF;
	SDL_Surface* mTextSurface;
	//Test
	Entity testEnt;
};