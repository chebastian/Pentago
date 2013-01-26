#include "SDLWrapper.h"
#include <iostream>
#include <Windows.h>
#include "InputManager.h"
#include "KeyEvent.h"

SDLWrapper::SDLWrapper(void)
{
	mKeysDown = new int[SDLK_LAST];

	for(int i = 0; i < SDLK_LAST; i++)
	{
		mKeysDown[i] = false;
	}

	mInputMgr = new InputManager();
	mElapsedTime = 1.0f;
	testEnt = Entity(0);

	mInputMgr->AddMouseListener(&testEnt);
}


SDLWrapper::~SDLWrapper(void)
{
}

void SDLWrapper::Initialize()
{
	if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}


	SDL_EnableUNICODE(SDL_ENABLE);
	mScreen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE | SDL_DOUBLEBUF);
	mIsRunning = true;
}

void SDLWrapper::RenderString(const std::string& str, int x, int y, int incolor)
{
	if(!TTF_WasInit())
	{
		if(TTF_Init() != -1)
		{
				mFontTTF = TTF_OpenFont("../media/fonts/ProFontWindows.ttf",16);
		}
	}

	if(str.length() <= 0)
		return;

	SDL_Color color,colorBG;
	color.r = 255; color.g = 0; color.b = 255;
	colorBG.r = 100; colorBG.g = 100; colorBG.b = 100;
	SDL_Rect rect, srcRect;
	rect.x = (Sint16)x; rect.y = (Sint16)y;
	int w = NULL;
	int h = NULL;

	color.b = (char)incolor;
	color.g = (Uint8)(incolor >> 8);
	color.r = (Uint8)(incolor >> 16);

	mTextSurface = TTF_RenderText_Solid(mFontTTF, str.c_str(), color);
	w = mTextSurface->w; h = mTextSurface->h;
	rect.w = (Uint16)w; rect.h = (Uint16)h;

	srcRect.x = 0; srcRect.y = 0; srcRect.w = (Uint16)w; srcRect.h = (Uint16)h;
	SDL_BlitSurface(mTextSurface, &srcRect, mScreen, &rect);

	SDL_FreeSurface(mTextSurface);

}


bool SDLWrapper::Update()
{
	static Uint32 lastTime = 0;
	Uint32 now = SDL_GetTicks();
	float elapsed = (now - lastTime)/1000.0f;
	mElapsedTime = elapsed;

	
	HandleInputFromSDL();

	lastTime = now;

	SDL_Flip(mScreen);
	ClearScreen();
	return mIsRunning;
}

void SDLWrapper::HandleInputFromSDL()
{
	SDL_Event evt;

	while(SDL_PollEvent(&evt))
	{
		KeyEvent event = KeyEvent();

		if(evt.type == SDL_QUIT)
			mIsRunning = false;
		if(evt.type == SDL_KEYDOWN)
		{
			event.Type = Event_Type::EVT_KEYDOWN;
			event.keyChar = static_cast<char>(evt.key.keysym.unicode);
			event.KeyCode = TranslateSDLKeyToKeyCodes(evt);
			mInputMgr->ProcessInput(event);
		}

		else if(evt.type == SDL_KEYUP)
		{
			event.Type = Event_Type::EVT_KEYRELEASED;
			event.keyChar = static_cast<char>(evt.key.keysym.unicode);
			event.KeyCode = TranslateSDLKeyToKeyCodes(evt);
			mInputMgr->ProcessInput(event);
		}

		else if(evt.type == SDL_MOUSEMOTION)
		{
			event.Type = Event_Type::EVT_MOUSEMOTION;
			event.mouseX = evt.motion.x;
			event.mouseY = evt.motion.y;
			mInputMgr->ProcessInput(event);
		}

	}

}

Key_Code SDLWrapper::TranslateSDLKeyToKeyCodes(SDL_Event& evt)
{
	Key_Code code = Key_Code::KC_NONE;
	if(evt.key.keysym.sym == SDLK_LEFT)
		code = Key_Code::KC_LEFT;
	if(evt.key.keysym.sym == SDLK_DOWN)
		code = Key_Code::KC_DOWN;
	if(evt.key.keysym.sym == SDLK_RIGHT)
		code = Key_Code::KC_RIGHT;
	if(evt.key.keysym.sym == SDLK_UP)
		code = Key_Code::KC_UP;
	if(evt.key.keysym.sym == SDLK_SPACE)
		code = Key_Code::KC_SPACE;
		
	return code;
}

void SDLWrapper::DrawPixel(SDL_Surface* screen, int x, int y, ColorRGB* rgb)
{
	Uint32 col = SDL_MapRGB(screen->format, rgb->r,rgb->g,rgb->b);
	if(SDL_MUSTLOCK(screen))
	{
		if(SDL_LockSurface(screen) < 0)
			return;
	}

	Uint32* pixel =	(Uint32*) screen->pixels + y * screen->pitch/4 +x;
	*pixel = col;

	if(SDL_MUSTLOCK(screen))
	{
		SDL_UnlockSurface(screen);
	}
}

void SDLWrapper::ClearScreen()
{
	SDL_Surface* screen = Screen();
	ColorRGB rgb = ColorRGB(0,0,0);

	Uint32 col = SDL_MapRGB(screen->format, rgb.r,rgb.g,rgb.b);
	//rgb = col;
	if(SDL_MUSTLOCK(screen))
	{
		if(SDL_LockSurface(screen) < 0)
			return;
	}

	for(int x = 0; x < mScreen->w; x++)
	{
		for(int y = 0; y < mScreen->h; y++)
		{
			Uint32* pixel =	(Uint32*) screen->pixels + y * screen->pitch/4 +x;
			*pixel = col;
		}
	}

	if(SDL_MUSTLOCK(screen))
	{
		SDL_UnlockSurface(screen);
	}

	//SDL_UpdateRect(screen, 0, 0, screen->w,screen->h);
}

bool SDLWrapper::IsKeyDown(SDLKey key)
{
	return mKeysDown[key] == 0;
}

float SDLWrapper::GetElapsedTime()
{
	static float lastTime = 0;
	Uint32 now = SDL_GetTicks();

	float elapsedTime = (now - lastTime)/1000.0f;

	lastTime = static_cast<float>(now);

	return elapsedTime;
}

void SDLWrapper::ClearInputBuffer()
{
}