#pragma once
#include "Enemy.h"

class Enemy_fly : public Enemy
{
public:
	Enemy_fly(SDL_Rect pos, std::vector<Actor*>** world, Object obj);
	~Enemy_fly();


	void Enemy_fly::render(SDL_Renderer * renderer, int time_passed, CoreEngine & core);
	


};

