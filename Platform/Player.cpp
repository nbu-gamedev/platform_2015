#include <algorithm>
#include "CoreEngine.h"
#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(SDL_Rect pos, std::vector<Actor*>** world)
{
    pos_rect = pos;
    real_x = pos.x;
    real_y = pos.y;
	grid = world;
    i_grid = get_grid_coords().first;
    j_grid = get_grid_coords().second;
    speed = 0;
    speed_y = 0;
    moving = false;
    jumping = false;
    falling = false;
    h_direction = 1;
    v_direction = 1;
    alive = true;
    completely_dead = false;
    end_level = false;
    if (!lives) lives  = 3;
}
void Player::move_player(int time)
{
    double moved = 0;

    if(jumping || falling)
    {
        // moving on y
        moved = time*(speed_y - gravity_acceleration *time/ 2000.) / 1000.;
        if(moved < 0) moved *= -1;
        speed_y += (-v_direction)*gravity_acceleration*time/1000;
        real_y += (-v_direction)*moved;
        pos_rect.y = real_y;
        if ( pos_rect.y > M_WINDOW_HEIGHT)
        {
            completely_dead = true;
        }
        else
        if( real_y < 0)
        {
            pos_rect.y = real_y = 0;
            speed_y = 0;
        }

        if (speed_y <= 0) v_direction = -1;

        if (speed_y >= terminal_velocity) speed_y = terminal_velocity;
    }

    if (moving && alive)
    {
        moved = std::min(time*(speed + acceleration*time/2000.)/1000., max_speed_player*time/1000.);
        if(moved < 0) moved *= -1;
        real_x += (h_direction)*moved;
        pos_rect.x = real_x;
        if ( pos_rect.x > M_WINDOW_WIDTH - pos_rect.w)
            pos_rect.x = real_x = M_WINDOW_WIDTH - pos_rect.w;
        else if( pos_rect.x < 0)
            pos_rect.x = real_x = 0;
        speed = std::min(speed + acceleration*time / 1000, max_speed_player);
    }

    if (!(jumping || falling || moving))
    {
        speed = 0;
    }

}
void Player::check_collisions()//(grid*)
{

    if(!alive) return;

    int i_pos = get_grid_coords().first;
    int j_pos = get_grid_coords().second;
    // check if collide with close objects
    for (int i = i_pos - 1; i <= i_pos + 1; i++)
    {
        for(int j = j_pos - 1; j <= j_pos + 1; j++)
        {
            if (i < 0 || i >= GRID_HEIGHT || j < 0 || j >= GRID_WIDTH) continue; // world ' out of bounds ' ?
			for (Actor* actor : grid[i][j])
			{
				if (overlap(actor) && !(dynamic_cast<Player*>(actor)))
				{
                    /*
					cout<<"overlap:: ["<<i_pos<<"]["<<j_pos<<"] & ["<<i<<"]["<<j<<"]"<<endl;
					cout<<pos_rect.x << " " << pos_rect.y << " " << pos_rect.x + pos_rect.w << " " << pos_rect.y + pos_rect.h<<endl;
					cout<<"\\ "<<actor->pos_rect.x << " " << actor->pos_rect.y << " " << actor->pos_rect.x + actor->pos_rect.w <<
					" " << actor->pos_rect.y + actor->pos_rect.h<<endl;
                    */
					if (dynamic_cast<Terrain*>(actor))
					{
						collide_with_Terrain(dynamic_cast<Terrain*>(actor));
					}
					if (dynamic_cast<Coin*>(actor) && !(dynamic_cast<Coin*>(actor)->taken))
					{
						get_coin(dynamic_cast<Coin*>(actor));
					}
					if (dynamic_cast<Enemy*>(actor))
					{
						die();
					}
					/*

					if (dynamic_cast<Exit*>(actor) && !Coin::coins_to_collect)
					{
					end_level = true;
					*/
				}
			}
        }
    }
    //check for any floor (not necessarily stable)
    //

    if(!alive || i_pos >= GRID_HEIGHT - 1 || jumping || falling) return;

    Terrain* floor = NULL;
    if(i_pos + 1 < GRID_HEIGHT && !grid[i_pos + 1][j_pos].empty() && dynamic_cast<Terrain*>(grid[i_pos + 1][j_pos][0])
            && dynamic_cast<Terrain*>(grid[i_pos + 1][j_pos][0]) -> pos_rect.y <= pos_rect.y + pos_rect.h + 1)
    {
        floor = dynamic_cast<Terrain*>(grid[i_pos + 1][j_pos][0]);

    }
    if(!floor && !(jumping || falling))
    {
        falling = true;
        moving = false;
        v_direction = -1;
        speed_y = 0;
    }
    else if (floor)
    {
        pos_rect.y = real_y = floor -> pos_rect.y - pos_rect.h - 1;
        speed_y = 0;
        v_direction = 1;
        jumping = falling = false;
    }
}

bool Player::update(int time_passed, Key_event* ke) // (int time_passed)
{
    if (ke && alive)
    {
        if (ke->left_pressed || ke->right_pressed)
        {
            moving = true;
            h_direction = ke->left_pressed ? -1 : 1;
        }
        else
        {
            moving  = false;
        }
        if (ke->jump_pressed && !(jumping || falling))
        {
            jumping = true;
            v_direction = 1;
            speed_y = jump_start_speed;
        }
    }

    move_player(time_passed);
    check_collisions();
    return update_grid_pos();
}

void Player::render(SDL_Renderer * renderer, int time_passed, CoreEngine & core)
{
	static SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
	static int lastUpdated = 0;
	static int frame = 0;
	lastUpdated += time_passed;
	if (lastUpdated > 50)
	{
		frame++;
		frame %= core.player_textures.size();
		lastUpdated -= 50;
		//lastUpdated = 0;
	}
	//TODO yavor / samir  make it start from first frame every time the player stops
	if (moving)
	{
		if (h_direction < 0)
		{
			// core.player_textures.size()-frame-1   //TODO test if frames are correct order
			SDL_RenderCopyEx( renderer, core.player_textures[frame], NULL, &pos_rect, 180.0f, NULL,flip);

		}
		else
		{
			SDL_RenderCopy(renderer, core.player_textures[frame], NULL, &pos_rect);
		}
	}
	else
	{
		frame = 0;
		if (h_direction < 0)
		{
			SDL_RenderCopyEx(renderer, core.player_textures[frame], NULL, &pos_rect, 180.0f, NULL, flip);
		}
		else
		{
			SDL_RenderCopy(renderer, core.player_textures[frame], NULL, &pos_rect);
		}
	}
}



void Player:: collide_with_Terrain(Terrain* terra)
{
    if(i_grid < terra -> i_grid)
    {
        if(j_grid == terra -> j_grid)
        {
            pos_rect.y = real_y = terra -> pos_rect.y - pos_rect.h - 1;
            speed_y = 0;
            jumping = falling = false;
        }
    }

    else if(i_grid == terra -> i_grid)
    {
        if (j_grid < terra -> j_grid)
        {
            pos_rect.x = real_x = terra -> pos_rect.x - pos_rect.w - 1;
        }
        else
        {
            pos_rect.x = real_x = terra -> pos_rect.x + terra -> pos_rect.w + 1;
        }

        moving = false;
        speed = 0;

       /* if (jumping)
        {
            jumping = false;
            falling = true;
            speed_y = 0;
        }*/
    }
    else
    {
        if(j_grid == terra -> j_grid)
        {
            pos_rect.y = real_y = terra -> pos_rect.y + terra -> pos_rect.w + 1;
            speed_y = 0;
        }
    }
}

void Player:: get_coin(Coin* coin)
{
    coin -> taken = true;
    Coin::coins_to_collect--;
}

void Player::die()
{
    lives--;
    alive = false;
    falling = true;
    moving = jumping = false;
    speed_y = speed = 0;
}

bool Player::update_grid_pos()
{

    int new_i_grid = get_grid_coords().first;
    int new_j_grid = get_grid_coords().second;

    // don't change position if dead (it's not neccessary)
    if ((new_i_grid == i_grid && new_j_grid == j_grid) || !alive)
        return false;

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

int Player::lives = 3;
