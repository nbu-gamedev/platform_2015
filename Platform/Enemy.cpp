#include "Enemy.h"
#include "CoreEngine.h"
 Enemy::Enemy (SDL_Rect pos, Actor*** world, int maxx, int minx, int spd, int direction = 1)
 {
	pos_rect = pos;
	grid = world;
	max_x = maxx;
	min_x = minx;
	speed = spd;
	this->direction = direction;
 }

 Enemy::Enemy(SDL_Rect rect, Actor*** world, Object obj)
 {

	pos_rect = rect;
	grid = world;
	type = obj;
	//max_x = min_x = rect.x;
	max_x = rect.x + 100;
	min_x = rect.x - 100;
	speed = 100;
	direction = 1;
	real_x = rect.x;

 }

#include <iostream>
 using namespace std;
void Enemy::update(int time_passed)
{
	real_x += (direction)*(speed * time_passed)/ 1000;
	pos_rect.x = real_x;
	if ( pos_rect.x > max_x) // 1280 == screen_width
	{
		pos_rect.x = max_x;
		direction = -1;
	}
	else if( pos_rect.x < min_x)
	{
		pos_rect.x = min_x;
		direction = 1;
	}

}

void Enemy::render(SDL_Renderer * renderer, int time_passed, CoreEngine & core)
{
	SDL_RenderCopy(renderer, core.enemy_textures[0], NULL, &pos_rect);
}
