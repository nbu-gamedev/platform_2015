#include <algorithm>
#include "CoreEngine.h"
#include "Player.h"
#include <iostream>
using namespace std;
Player::Player(SDL_Rect pos/*, SDL_Rect img*/)
{
    pos_rect = pos;
    real_x = pos.x;
    real_y = pos.y;
    //img_rect = img;
    speed = 0;
    speed_y = 0;
    moving = false;
    jumping = false;
    falling = false;
    h_direction = 1;
    v_direction = 1;
    acceleration = max_acceleration;
    alive = true;
}
void Player::move_player(int time)
{
    double moved = 0;

    if(jumping || falling)
    {
        // moving on y
        moved = time*(speed_y - gravity_acceleration * time/ 2000.) / 1000.;
        if(moved < 0) moved *= -1;
        speed_y += (-v_direction)*gravity_acceleration*time/1000;
        real_y += (-v_direction)*moved;
        pos_rect.y = real_y;
        if ( pos_rect.y > M_WINDOW_HEIGHT - pos_rect.h)
        {
            pos_rect.y = real_y = M_WINDOW_HEIGHT - pos_rect.h;
            jumping = false;
            speed_y = 0;
            // if (out of screen) die;
        }
        else
        if( real_y < 0)
        {
            pos_rect.y = real_y = 0;
            speed_y = 0;
        }

        if (speed_y <= 0) v_direction = -1;
    }

    if (moving && !falling)
    {
        moved = std::min(time*(speed + acceleration*time/2000.)/1000., max_speed_player*time/1000.);
        real_x += (h_direction)*moved;
        pos_rect.x = real_x;
        if ( pos_rect.x > M_WINDOW_WIDTH - pos_rect.w)
            pos_rect.x = real_x = M_WINDOW_WIDTH - pos_rect.w;
        else if( pos_rect.x < 0)
            pos_rect.x = real_x = 0;
        speed = std::min(speed + acceleration*time / 1000, max_speed_player);

       // acceleration = std::max((int)0.95*time/1000*acceleration, max_acceleration/2);
       // std::cout << speed <<std::endl;
    }

    if (!(jumping || falling || moving))
    {
        speed = 0;
    }

}
void Player::check_collisions(Actor*** grid)//(grid*)
{

    if(!alive) return;

    int i_pos= getGridCoords().first;
    int j_pos = getGridCoords().second;
    // check if collide with close objects
    for (int i = i_pos - 1; i <= i_pos + 1; i++)
    {
        for(int j = j_pos - 1; j <= j_pos + 1; j++)
        {
            if (i < 0 || i >= GRID_HEIGHT || j < 0 || j >= GRID_WIDTH) break; // world ' out of bounds ' ?
            if (grid[i][j] && overlap(grid[i][j]))
            {
                Actor* actor = grid[i][j];
                if (dynamic_cast<terrain*>(actor))
                {
                  //  collide_with_terrain(dynamic_cast<terrain*>(actor));
                }
                if (dynamic_cast<Coin*>(actor) && !dynamic_cast<Coin*>(actor)->taken)
                {
                    get_coin(dynamic_cast<Coin*>(actor));
                }
                if (dynamic_cast<Enemy*>(actor))
                {
                    die();
                }
            }
        }
    }
    //check for any floor (not necessarily stable)
    //

    if(!alive || i_pos >= GRID_HEIGHT - 1 || v_direction > 0) return;

    terrain* floor = NULL;
    if (grid[i_pos][j_pos] && dynamic_cast<terrain*>(grid[i_pos][j_pos]) && overlap(dynamic_cast<terrain*>(grid[i_pos][j_pos])))

    {
        floor = dynamic_cast<terrain*>(grid[i_pos][j_pos]);
    }
    else if(i_pos + 1 < GRID_HEIGHT && grid[i_pos + 1][j_pos] && dynamic_cast<terrain*>(grid[i_pos + 1][j_pos])
            && dynamic_cast<terrain*>(grid[i_pos + 1][j_pos]) -> pos_rect.y <= pos_rect.y + pos_rect.h + 1)
    {
        floor = dynamic_cast<terrain*>(grid[i_pos + 1][j_pos]);
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
        jumping = falling = false;
    }
}

void Player::update(Actor*** grid, int time_passed, Key key, Type key_type)
{
    if (alive && (key == LEFT || key == RIGHT))
    {
        if(key_type == PRESSED && !falling)
        {
            moving = true;
            h_direction = key == LEFT ? -1 : 1;
            acceleration = max_acceleration;
        }
        else
            moving  = false;
        }
     if (alive && (key == JUMP && !jumping) && key_type == PRESSED)
     {
        jumping = true;
        v_direction = 1;
        speed_y = jump_start_speed;
     }

    move_player(time_passed);
    check_collisions(grid);

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



void Player:: collide_with_terrain(terrain* terra)
{

}
/*void Player:: collide_with_enemy(Enemy* enemy)
{

}*/
void Player:: get_coin(Coin* coin)
{
    coin -> taken = true;
    Coin::taken_coins++;
}

void Player::die()
{
    alive = false;
    falling = true;
    moving = jumping = false;
    speed_y = 0;
}

