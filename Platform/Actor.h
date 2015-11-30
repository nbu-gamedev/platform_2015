#pragma once
#ifdef __linux__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <vector>
#include "Input_Handler.h"
enum Object
{
	GROUND, GROUND_DIRT, PLAYER, SLIME
};

#include <utility>
#include "Globals.h"

class CoreEngine;
class Actor
{

public:
	virtual ~Actor();
	virtual void update();
	virtual void update(Actor*** grid, int time_passed, Key key, Type key_type) = 0;
	virtual void render(SDL_Renderer* renderer , int time_passed, CoreEngine &core) = 0;
	std::pair< std::pair<int,int>, std::pair<int,int> > getGridCoords();
	bool overlap(Actor* actor);

	SDL_Rect pos_rect;
	SDL_Rect img_rect;

	int speed; //
	// The number in the World::loadedObjects
	int loadedNumber;
};
