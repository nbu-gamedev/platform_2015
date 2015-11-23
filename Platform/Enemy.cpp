#include "Enemy.h"

 Enemy::Enemy (SDL_Rect pos, int maxx, int minx, int spd, int direction = 1)
 {
    pos_rect = pos;
    max_x = maxx;
    min_x = minx;
    speed = spd;
    this->direction = direction;
 }


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
}
