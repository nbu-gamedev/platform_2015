#pragma once
#ifdef __linux__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

class Actor
{

public:
	virtual void update();
	virtual void render();

	SDL_Rect pos_rect;
	SDL_Rect img_rect;
	int speed; //
	// The number in the World::loadedObjects
	int loadedNumber;
};
