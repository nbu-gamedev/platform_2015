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
	Enemy(SDL_Rect pos, std::vector<Actor*>** world, Object obj);

	Object type;
	virtual bool update(int time_passed, Key_event* ke);
	virtual void render(SDL_Renderer* renderer, int time_passed, CoreEngine &core);
	void collide_with_Terrain();
	bool update_grid_pos();
    bool dead;
protected:

	std::vector<Actor*>** grid;
	int direction;
	int min_x, max_x; // range for movement, when reached max or min, change direction
	float real_x,real_y; //if not float, movement can't be registered because of flooring
	int speed_y;
    bool falling;
};


