#include "SDLWrapper.h"
#include <iostream>
#include <Windows.h>
#include "InputManager.h"
#include "KeyEvent.h"
#include <sstream>

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
	mCurrentFPS = 0;
	mTimeUntilNextSecond = 1.0f;
	mInputMgr->AddMouseListener(&testEnt);
	FrameLimiter = true;
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
				mFontTTF = TTF_OpenFont("../../media/fonts/ProFontWindows.ttf",16);
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

	renderFPS(SFMath::Vector2Di(400,10));
	SDL_Flip(mScreen);
	ClearScreen();

	if(FrameLimiter)
	{
		if(elapsed <= 1.0f/30.0f)
			Sleep(20);
	}

	return mIsRunning;
}

void SDLWrapper::renderFPS(const SFMath::Vector2Di& pos)
{
	std::stringstream ss;
	ss << mCurrentFPS;
	std::string elapsedStr = ss.str();
	RenderString(elapsedStr,pos.x,pos.y);
	mFrameCounter++;
	mTimeUntilNextSecond -= mElapsedTime;
	
	if(mTimeUntilNextSecond <= 0.0f)
	{
		mTimeUntilNextSecond = 1.0f;
		mCurrentFPS = mFrameCounter;
		mFrameCounter = 0;
	}	
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

		else if(evt.type == SDL_MOUSEBUTTONDOWN)
		{
			event.Type = Event_Type::EVT_MOUSEPRESSED;
			mInputMgr->ProcessInput(event);
		}

		else if(evt.type == SDL_MOUSEBUTTONUP)
		{
			event.Type = Event_Type::EVT_MOUSERELEASED;
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
	if(evt.key.keysym.sym == SDLK_ESCAPE)
		code = Key_Code::KC_ESC;
	if(evt.key.keysym.sym == SDLK_RETURN)
		code = Key_Code::KC_ENTER;
	if(evt.key.keysym.sym == SDLK_BACKSPACE)
		code = Key_Code::KC_BACKSPACE;
		
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
	ColorRGB rgb = ColorRGB(100,100,100);

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

SDL_Surface* SDLWrapper::createNewRotatedSurface(SDL_Surface* pSrc, SDL_Rect src_rect,int degree)
{
	SDL_Surface* res;

	float radians = ((2.0f*3.14f)*degree)/360;
	SDL_Surface* src = createNewSubSurface(pSrc,src_rect);
	rgba* src_pixles = reinterpret_cast<rgba*>(src->pixels);
	
	float cosine = cos(radians);
	float sine = sin(radians);

	float sinH = src->h*sine;
	float cosH = src->h*cosine;
	float sinW = src->w*sine;
	float cosW = src->w*cosine;

	SFMath::Vector2Df p1(-sinH, cosH);
	SFMath::Vector2Df p2(cosW-sinH, cosH+sinW);
	SFMath::Vector2Df p3(cosW, sinW);
	SFMath::Vector2Df p4(-sinW, sinH);
	
	SFMath::Vector2Df pMin(min(0,min(p1.x, min(p2.x, min(p3.x,p4.x)))),
						min(0,min(p1.y, min(p2.y, min(p3.y,p4.y)))));

	SFMath::Vector2Df pMax(max(0,max(p1.x, max(p2.x, max(p3.x,p4.x)))),
						max(0,max(p1.y, max(p2.y, max(p3.y,p4.y)))));

	int dstW = (int)ceil((pMax.x)-pMin.x);
	int dstH = (int)ceil((pMax.y)-(pMin.y));

	res = SDL_CreateRGBSurface(SDL_HWSURFACE,dstW,dstH,32,0,0,0,255);
	rgba* dst_pixles = reinterpret_cast<rgba*>(res->pixels);
	for(int x = 0; x < dstW; x++)
	{
		for(int y = 0; y < dstH; y++)
		{
			int SrcBitmapx=(int)((x+pMin.x)*cosine+(y+pMin.y)*sine); 
			int SrcBitmapy=(int)((y+pMin.y)*cosine-(x+pMin.x)*sine);
			int iw =src->w;
			int ih =src->h;
			
			if(SrcBitmapx >= 0 && SrcBitmapx <= iw &&
				SrcBitmapy >= 0 && SrcBitmapy <= ih)
			{
				dst_pixles[x+y*dstW] = src_pixles[SrcBitmapx+SrcBitmapy*src->w];
			}
			else
			{
				Color_RGBA alpha = Color_RGBA();
				alpha.a = 0;
				alpha.b = 255;
				alpha.r = 255;
				alpha.g = 0;
				dst_pixles[x+y*dstW] = alpha;
			}
		}
	}
	
	SDL_FreeSurface(src);
	return res;
}

SDL_Surface* SDLWrapper::createNewSubSurface(SDL_Surface* src, SDL_Rect src_rect)
{
	SDL_Surface* xres = SDL_CreateRGBSurface(SDL_HWSURFACE,src_rect.w,src_rect.h,32,0,0,0,255);
	Color_RGBA* dstPixles = reinterpret_cast<Color_RGBA*>(xres->pixels);
	Color_RGBA* srcPixles = reinterpret_cast<Color_RGBA*>(src->pixels);
	
	for(int y = 0; y < src_rect.h; y++)
	{
		for(int x = 0; x < src_rect.w; x++)
		{
			dstPixles[x+y*src_rect.w] = srcPixles[(x+src_rect.x)+(y+src_rect.y)*src->w];
		}
	}

	return xres;
}

void SDLWrapper::pasteSurfaceIntoSurface(SDL_Surface* dst, SDL_Surface* src, const SFMath::Vector2Di& offset)
{
	Color_RGBA* dstPixels = reinterpret_cast<Color_RGBA*>(dst->pixels);
	Color_RGBA* srcPixels = reinterpret_cast<Color_RGBA*>(src->pixels);
	
	for(int y = 0; y < src->h; y++)
	{
		for(int x = 0; x < src->w; x++)
		{
			dstPixels[(x+offset.x)+(y+offset.y)*dst->w] = srcPixels[x+y*src->w];
		}
	}
}