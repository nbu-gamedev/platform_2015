#include <algorithm>
#include "Player.h"
#include <iostream>

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

    if(jumping)
    {
        // moving on y
        moved = time*(speed_y - gravity_acceleration * time/ 2000.) / 1000.;
        speed_y += (-v_direction)*gravity_acceleration*time/1000;
        real_y += (-v_direction)*moved;
        pos_rect.y = real_y;
        if ( pos_rect.y > 630 - pos_rect.h) //630 == screen_height
        {
            pos_rect.y = 630 - pos_rect.h;
            jumping = false;
            speed_y = 0;
        }
        else if( pos_rect.y < 0)
        {
            pos_rect.y = 0;
            speed_y = 0;
        }

        if (speed_y <= 0) v_direction = -1;
    }

    else if(falling)
    {
        // moving on y
        moved = time*(speed_y - gravity_acceleration * time/ 2000.) / 1000.;
        speed_y += (-v_direction)*gravity_acceleration*time/1000;
        real_y += (-v_direction)*moved;
        pos_rect.y = real_y;
        if ( alive && pos_rect.y > 630 - pos_rect.h) //630 == screen_height
        {
            pos_rect.y = 630 - pos_rect.h;
            falling = false;
            speed_y = 0;
        }
        else if( pos_rect.y < 0)
        {
            pos_rect.y = 0;
            speed_y = 0;
        }

    }

    //else
    if (moving)
    {
        moved = std::min(time*(speed + acceleration*time/2000.)/1000., max_speed_player*time/1000.);
        real_x += (h_direction)*moved;
        pos_rect.x = real_x;
        if ( pos_rect.x > 1330 - pos_rect.w) // 1330 == screen_width
            pos_rect.x = 1330 - pos_rect.w;
        else if( pos_rect.x < 0)
            pos_rect.x = 0;
        speed = std::min(speed + acceleration*time / 1000, max_speed_player);

       // acceleration = std::max((int)0.95*time/1000*acceleration, max_acceleration/2);
       // std::cout << speed <<std::endl;
    }

    else
    {
        speed = 0;
    }

}
void Player::check_collisions(Actor*** grid)//(grid*)
{
    int i_beg_grid = getGridCoords().first.first;
    int j_beg_grid = getGridCoords().first.second;
    int i_end_grid = getGridCoords().second.first;
    int j_end_grid = getGridCoords().second.second;

    // check if collide with close objects
    for (int i = i_beg_grid; i<= i_end_grid; i++)
    {
        for(int j = j_beg_grid; j <= j_end_grid; j++)
        {
            if (i < 0 || i > 10 || j < 0 || j > 18) return; // world ' out of bounds ' ?
            if (grid[i][j] && overlap(grid[i][j]))
            {
                Actor* actor = grid[i][j];
                if (dynamic_cast<terrain*>(actor))
                {
                    collide_with_terrain(dynamic_cast<terrain*>(actor));
                }
                 if (dynamic_cast<Coin*>(actor) && !dynamic_cast<Coin*>(actor)->taken)
                {
                    get_coin(dynamic_cast<Coin*>(actor));
                }
            }
        }
    }
}

void Player::update(Actor*** grid, int time_passed, Key key, Type key_type)
{
    if (key == LEFT || key == RIGHT)
    {
        if(key_type == PRESSED)
        {
            moving = true;
            h_direction = key == LEFT ? -1 : 1;
            acceleration = max_acceleration;
        }
        else
            moving  = false;
        }
     if (key == JUMP && !jumping)
     {
        jumping = true;
        v_direction = 1;
        speed_y = jump_start_speed;
     }

    move_player(time_passed);
    check_collisions(grid);

}

void Player:: collide_with_terrain(terrain* terra)
{

}
void Player:: collide_with_enemy(Enemy* enemy)
{

}
void Player:: get_coin(Coin* coin)
{
    coin -> taken = true;
    Coin::taken_coins++;
}

