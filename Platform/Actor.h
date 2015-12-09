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
	virtual bool update(int time_passed, Key_event* ke) = 0;
	virtual void render(SDL_Renderer* renderer , int time_passed, CoreEngine &core) = 0;
	//std::pair< std::pair<int,int>, std::pair<int,int> > get_grid_coords();
	std::pair<int,int> get_grid_coords();
	bool overlap(Actor* actor);

	SDL_Rect pos_rect;
	SDL_Rect img_rect;

    int i_grid, j_grid;
	int speed; //
	// The number in the World::loadedObjects
	int loadedNumber;
};
