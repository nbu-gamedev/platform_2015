#include "Enemy.h"
#include "CoreEngine.h"
 Enemy::Enemy (SDL_Rect pos, Actor*** world, int maxx, int minx, int spd, Object obj, int direction = 1)
 {
	pos_rect = pos;
    real_x = pos.x;
    real_y = pos.y;
	grid = world;
	type = obj;
    i_grid = get_grid_coords().first;
    j_grid = get_grid_coords().second;
	max_x = maxx;
	min_x = minx;
	speed = spd;
	speed_y = 0;
	falling = false;
	this->direction = direction;


	if(max_x > M_WINDOW_WIDTH - pos.w) max_x = M_WINDOW_WIDTH - pos.w;
	if(min_x > M_WINDOW_WIDTH - pos.w) min_x = M_WINDOW_WIDTH - pos.w;
	if(max_x < 0) max_x = 0;
	if(min_x < 0) min_x = 0;
	if (min_x > max_x) swap(max_x,min_x);

 }

 Enemy::Enemy(SDL_Rect pos, Actor*** world, Object obj)
 {

	pos_rect = pos;
    real_x = pos.x;
    real_y = pos.y;
	grid = world;
	type = obj;
	//max_x = min_x = rect.x;
    i_grid = get_grid_coords().first;
    j_grid = get_grid_coords().second;
	max_x = pos.x + 140 * SCALE_FACTOR;
	min_x = pos.x - 140 * SCALE_FACTOR;
	speed = 100;
	speed_y = 0;
	direction = 1;
	falling = false;


	if(max_x > M_WINDOW_WIDTH - pos.w) max_x = M_WINDOW_WIDTH - pos.w;
	if(min_x > M_WINDOW_WIDTH - pos.w) min_x = M_WINDOW_WIDTH - pos.w;
	if(max_x < 0) max_x = 0;
	if(min_x < 0) min_x = 0;
	if (min_x > max_x) swap(max_x,min_x);

 }

void Enemy::update(int time_passed)
{
    double moved;
    if(!falling)
    {
        real_x += (direction)*(speed * time_passed)/ 1000;
        pos_rect.x = real_x;
        if ( pos_rect.x > max_x)
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
    else
    {
        double moved = time_passed*(speed_y - gravity_acceleration * time_passed/ 2000.) / 1000.;
        if (moved < 0) moved *= -1;
        speed_y += gravity_acceleration*time_passed/1000;
        real_y += moved;
        pos_rect.y = real_y;
        if ( pos_rect.y > M_WINDOW_HEIGHT - pos_rect.h)
        {
            pos_rect.y = real_y = M_WINDOW_HEIGHT - pos_rect.h;
            falling = false;
            speed_y = 0;
        }
    }
	collide_with_terrain();
    update_grid_pos();
}

void Enemy::render(SDL_Renderer * renderer, int time_passed, CoreEngine & core)
{
	SDL_RenderCopy(renderer, core.enemy_textures[0], NULL, &pos_rect);
}


void Enemy::update_grid_pos()
{
    i_grid = get_grid_coords().first;
    j_grid = get_grid_coords().second;

}

void Enemy::collide_with_terrain()
{
    int i_pos = get_grid_coords().first;
    int j_pos = get_grid_coords().second;
    bool collide = false;
    terrain* terra = NULL;
    // check if collide with close objects
    for (int i = i_pos - 1; i <= i_pos + 1; i++)
    {
        for(int j = j_pos - 1; j <= j_pos + 1; j++)
        {
            if (i < 0 || i >= GRID_HEIGHT || j < 0 || j >= GRID_WIDTH) continue; // world ' out of bounds ' ?
            if (grid[i][j] && overlap(grid[i][j]) && dynamic_cast<terrain*>(grid[i][j]))
            {
                terra = dynamic_cast<terrain*>(grid[i][j]);
                collide = true;
                if(i_grid < terra -> i_grid && j_grid == terra -> j_grid)
                {
                    pos_rect.y = real_y = terra -> pos_rect.y - pos_rect.h - 1;
                    speed_y = 0;
                    falling = false;
                }
                else if(i_grid == terra -> i_grid && !falling)
                {
                    if (j_grid < terra -> j_grid)
                    {
                        pos_rect.x = real_x = terra -> pos_rect.x - pos_rect.w - 1;
                    }
                    else
                    {
                        pos_rect.x = real_x = terra -> pos_rect.x + terra -> pos_rect.w + 1;
                    }
                    direction *= -1;
                }
            }
        }
    }
    terra = NULL;
    //check for any floor
    if(i_pos >= GRID_HEIGHT - 1) return;
    if(i_pos + 1 < GRID_HEIGHT && grid[i_pos + 1][j_pos] && dynamic_cast<terrain*>(grid[i_pos + 1][j_pos])
            && dynamic_cast<terrain*>(grid[i_pos + 1][j_pos]) -> pos_rect.y <= pos_rect.y + pos_rect.h + 1)
    {
        terra = dynamic_cast<terrain*>(grid[i_pos + 1][j_pos]);
    }

    if(!terra && !falling)
    {
        falling = true;
        speed_y = 0;
    }
    else if (terra)
    {
        pos_rect.y = real_y = terra -> pos_rect.y - pos_rect.h - 1;
        speed_y = 0;
        falling = false;
    }

}
