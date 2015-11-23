#pragma once
#ifdef __linux__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <utility>

class Actor
{

public:
    virtual ~Actor();
	virtual void update();
	virtual void render();
	std::pair< std::pair<int,int>, std::pair<int,int> > getGridCoords();
    bool overlap(Actor* actor);

	SDL_Rect pos_rect;
	SDL_Rect img_rect;
	int speed; //
	// The number in the World::loadedObjects
	int loadedNumber;
};
