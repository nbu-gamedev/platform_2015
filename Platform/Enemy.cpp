#include "Enemy.h"

 Enemy::Enemy (SDL_Rect pos, int maxx, int minx, int spd, int direction = 1)
 {
    pos_rect = pos;
    max_x = maxx;
    min_x = minx;
    speed = spd;
    this->direction = direction;
 }

 Enemy::Enemy(SDL_Rect rect, Object obj)
 {
	
	pos_rect = rect;
	type = obj;
	//max_x = min_x = rect.x;
	max_x = rect.x + 200;
	min_x = rect.x - 200;
	speed = 100;
	direction = 1;
	real_x = rect.x+rect.w/2;
	 
 }

#include <iostream>
 using namespace std;
void Enemy::update(Actor*** grid, int time_passed)
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
	else
	{
		cout << pos_rect.x << endl;

	}
}
