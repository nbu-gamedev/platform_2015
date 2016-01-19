#pragma once
#include "Enemy.h"

class Enemy_fly : public Enemy
{
public:
	Enemy_fly(SDL_Rect pos, std::vector<Actor*>** world, Object obj);
	~Enemy_fly();


	void render(SDL_Renderer * renderer, int time_passed, CoreEngine & core);
    bool update(int time_passed, Key_event* ke);
    void die();
	double radians;
};

