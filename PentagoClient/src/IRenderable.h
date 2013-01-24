#pragma once

#include "SDL.h"
class Renderer;

class IRenderable
{
public:
	virtual void Render(SDL_Surface* screen) = 0;
	virtual int GetLayer() = 0;
};

