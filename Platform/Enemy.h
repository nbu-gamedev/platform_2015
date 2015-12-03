#pragma once
#include "Actor.h"

/*
	Enemy is moving with constant speed
	have range of movement which shoud be range in only one platform (for now)
	=> cannot fall from platforms (for now)
*/

class Enemy :public Actor
{
public:
	// if enemy is static (not moving): maxx = minx = pos.x && spd = 0
	Enemy (SDL_Rect pos, Actor*** world, int maxx, int minx, int spd, int direction);
	Enemy(SDL_Rect rect, Actor*** world, Object obj);

	Object type;
	void update(int time_passed);
	virtual void update(int time_passed, Key_event* ke)
	{
		update(time_passed);
	}
	void render(SDL_Renderer* renderer, int time_passed, CoreEngine &core);
private:

    Actor*** grid;
	int direction;
	int min_x, max_x; // range for movement, when reached max or min, change direction
	float real_x,real_y; //if not float, movement can't be registered because of flooring

};


