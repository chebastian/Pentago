#include "Entity.h"
#include "InputManager.h"
#pragma warning( disable : 4100 )

Entity::Entity(const int& id)
{
	mEntityID = id;
	mPosition = SFMath::Vector2Di(100,100);
}


Entity::~Entity(void)
{
}

void Entity::Render(SDL_Surface* screen)
{
	SDL_Rect r;
	r.x = static_cast<Sint16>(mPosition.x);
	r.y = static_cast<Sint16>(mPosition.y);
	r.w = 10; r.h = 10;
	SDL_FillRect(screen, &r,0xFF00FFFF);
}

void Entity::OnClicked(const SFMouse* mouse)
{
}

void Entity::OnMouseOver(const SFMouse* mouse)
{
}

void Entity::OnMouseDown(const SFMouse* mouse)
{
}

void Entity::OnMouseReleased(const SFMouse* mouse)
{
}

void Entity::OnMouseMove(const SFMouse* mouse)
{
	mPosition.x = mouse->X();
	mPosition.y = mouse->Y();
}

void Entity::OnMouseDrag(const SFMouse* mouse)
{
}

bool Entity::CheckMouseOver(const SFMouse* mouse)
{
	return false;
}
