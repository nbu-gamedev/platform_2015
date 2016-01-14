#include "Enemy_fly.h"
#include "CoreEngine.h"


Enemy_fly::Enemy_fly(SDL_Rect pos, std::vector<Actor*>** world, Object obj)
	: Enemy(pos, world,obj)
{
}

Enemy_fly::~Enemy_fly()
{
}


void Enemy_fly::render(SDL_Renderer * renderer, int time_passed, CoreEngine & core)
{
	last_rendered += time_passed;
	if (last_rendered > 100)
	{
		frame++;
		frame %= core.enemy_fly_textures.size();
		last_rendered -= 100;
	}

	if (direction < 0)
	{
		SDL_RenderCopy(renderer, core.enemy_fly_textures[frame], NULL, &pos_rect);

	}
	else
	{
		SDL_RenderCopyEx(renderer, core.enemy_fly_textures[frame], NULL, &pos_rect, 180.0f, NULL, SDL_FLIP_VERTICAL);
	}
}

bool Enemy_fly::update(int time_passed, Key_event* ke)
{
    if(!dead)
    {
        real_x += (direction)*(speed * time_passed)/ 1000;
        pos_rect.x = real_x;
        if ( pos_rect.x >  M_WINDOW_WIDTH - pos_rect.w )
        {
            pos_rect.x =  M_WINDOW_WIDTH - pos_rect.w;
            direction *= -1;
        }
        else if (pos_rect.x > max_x)
        {
            pos_rect.x =  max_x;
            direction *= -1;
        }
        else if( pos_rect.x < 0)
        {
            pos_rect.x = 0;
            direction *= 1;
        }
        else if (pos_rect.x < min_x)
        {
            pos_rect.x =  min_x;
            direction *= -1;
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

        Terrain* floor = NULL;
        if(i_grid + 1 < GRID_HEIGHT && !grid[i_grid + 1][j_grid].empty() && dynamic_cast<Terrain*>(grid[i_grid + 1][j_grid][0])
                && dynamic_cast<Terrain*>(grid[i_grid + 1][j_grid][0]) -> pos_rect.y <= pos_rect.y + pos_rect.h + 1)
        {
            floor = dynamic_cast<Terrain*>(grid[i_grid + 1][j_grid][0]);
        }
        if (floor)
        {
            pos_rect.y = real_y = floor -> pos_rect.y - pos_rect.h - 1;
            speed_y = 0;
            falling = false;
        }
    }
    return update_grid_pos();
}

void Enemy_fly::die()
{
    dead = true;
    falling = true;
}
