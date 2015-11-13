#pragma once
#include <algorithm>
#include "Player.h"

Player::Player(SDL_Rect pos/*, SDL_Rect img*/)
{
    pos_rect = pos;
    real_x = pos.x;
    real_y = pos.y;
    //img_rect = img;
    speed = 0;
    jump_height = max_jump_height/2;
    moving = false;
    h_direction = 1;
    v_direction = 0;
}
void Player::move_player(int time)
{
    float moved = 0;
    if (moving)
    {
        moved = std::min(time*(speed +(acceleration*time/2.)/1000.)/1000., max_speed_player*time/1000.);
        real_x += (h_direction)*moved;
        pos_rect.x = real_x;
        if ( pos_rect.x > 1280 - pos_rect.w) // 1280 == screen_width
            pos_rect.x = 1280 - pos_rect.w;
        else if( pos_rect.x < 0)
            pos_rect.x = 0;
        speed = std::min(speed + acceleration*time / 1000, max_speed_player);
    }
    // plyzgane
  /*  else if ()
    {
        moved = std::max(time*(speed -(acceleration*time/2)/1000)/1000, 0);
        pos_rect.x += (h_direction)*moved;
        if ( pos_rect.x > 1280 - pos_rect.w)
            pos_rect.x = 1280 - pos_rect.w;
        else if( pos_rect.x < 0)
            pos_rect.x = 0;
        speed = std::max(speed - acceleration*time / 1000, 0);
    }
    //plavno spirane
    else if (!moving && !v_direction && speed > 0)
    {

    }
    //jumpig
    else if(!moving && v_direction)
    {

    }*/
    else
    {
        speed = 0;
    }

}
void Player::check_collisions()//(grid*)
{
    int x_grid = getGridCoords().first;
    int y_grid = getGridCoords().second;

    // check for platform
    /*

    */
    // check for enemy
    /*

    */
    // check for coins
    /*

    */
}

void Player::update(int time_passed, Key key, Type key_type)
{
    if (key == LEFT || key == RIGHT)
    {
        if(key_type == PRESSED)
        {
            moving = true;
            h_direction = key == LEFT ? -1 : 1;
        }
        else
            moving  = false;
        }
     if (key == UP)
     {
       //jump
     }

    move_player(time_passed);
    check_collisions();

}
std::pair<int,int> Player::getGridCoords()
{
    int x_grid = pos_rect.x / 70;// PixelPerTile;
    int y_grid = pos_rect.y / 70; //PixelPerTile;
    return std::make_pair(x_grid,y_grid);
}
