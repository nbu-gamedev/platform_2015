#pragma once

#include "Actor.h"

class World
{
public:
	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;
	static const int PIXEL_PER_TILE = 20;
	static const int GRID_WIDTH = SCREEN_WIDTH / PIXEL_PER_TILE;
	static const int GRID_HEIGHT = SCREEN_HEIGHT / PIXEL_PER_TILE;
	Actor* worldGrid[GRID_HEIGHT][GRID_WIDTH] = {};

};