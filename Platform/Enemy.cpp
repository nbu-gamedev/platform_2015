#include "Enemy.h"
#include "CoreEngine.h"

 Enemy::Enemy(SDL_Rect pos, std::vector<Actor*>** world, Object obj)
 {

	pos_rect = pos;
    real_x = pos.x;
    real_y = pos.y;
	grid = world;
	type = obj;
    i_grid = get_grid_coords().first;
    j_grid = get_grid_coords().second;
    // if(type == "static enemy" (??)) pos.x*SCALE_FACTOR;
	speed = 100;
	speed_y = 0;
	direction = 1;
	falling = false;
 }

bool Enemy::update(int time_passed, Key_event* ke)
{

     // if(type == "static enemy" (??)) retuen;
    if(!falling)
    {
        real_x += (direction)*(speed * time_passed)/ 1000;
        pos_rect.x = real_x;
        if ( pos_rect.x >  M_WINDOW_WIDTH - pos_rect.w)
        {
            pos_rect.x =  M_WINDOW_WIDTH - pos_rect.w;
            direction = -1;
        }
        else if( pos_rect.x < 0)
        {
            pos_rect.x = 0;
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
	collide_with_Terrain();
   return update_grid_pos();
}

void Enemy::render(SDL_Renderer * renderer, int time_passed, CoreEngine & core)
{
	static SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
	static int lastUpdated = 0;
	static int frame = 0;
	lastUpdated += time_passed;
	if (lastUpdated > 1000)
	{
		frame++;
		frame %= core.enemy_textures.size();
		lastUpdated -= 1000;
	}

		if (direction < 0)
		{
			SDL_RenderCopy(renderer, core.enemy_textures[frame], NULL, &pos_rect);

		}
		else
		{
			SDL_RenderCopyEx(renderer, core.enemy_textures[frame], NULL, &pos_rect, 180.0f, NULL, flip);
		}
}


bool Enemy::update_grid_pos()
{
    int new_i_grid = get_grid_coords().first;
    int new_j_grid = get_grid_coords().second;

    if ((new_i_grid == i_grid && new_j_grid == j_grid)
        || new_i_grid < 0 || new_i_grid >= GRID_HEIGHT
        || new_j_grid < 0 || new_j_grid >= GRID_WIDTH
        ) return false;

    for (int k = 0; k < grid[i_grid][j_grid].size(); k++)
    {
        if (grid[i_grid][j_grid][k] == this )
        {
            //delete old player
            grid[i_grid][j_grid].erase (grid[i_grid][j_grid].begin() + k);
            grid[new_i_grid][new_j_grid].push_back(this);
            i_grid = new_i_grid;
            j_grid = new_j_grid;
            return true;
        }
    }
    return false;
}

void Enemy::collide_with_Terrain()
{
    int i_pos = get_grid_coords().first;
    int j_pos = get_grid_coords().second;
    Terrain* terra = NULL;
    // check if collide with close objects
    for (int i = i_pos - 1; i <= i_pos + 1; i++)
    {
        for(int j = j_pos - 1; j <= j_pos + 1; j++)
        {
            if (i < 0 || i >= GRID_HEIGHT || j < 0 || j >= GRID_WIDTH) continue; // world ' out of bounds ' ?
			for (Actor* actor : grid[i][j])
			{
				if (overlap(actor) && dynamic_cast<Terrain*>(actor) )
				{
					terra = dynamic_cast<Terrain*>(actor);
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
    }
    terra = NULL;
    //check for any floor
    if(i_pos >= GRID_HEIGHT - 1) return;

    if(i_pos + 1 < GRID_HEIGHT && !grid[i_pos + 1][j_pos].empty() && dynamic_cast<Terrain*>(grid[i_pos + 1][j_pos][0])
            && dynamic_cast<Terrain*>(grid[i_pos + 1][j_pos][0]) -> pos_rect.y <= pos_rect.y + pos_rect.h + 1)
    {
        terra = dynamic_cast<Terrain*>(grid[i_pos + 1][j_pos][0]);
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
