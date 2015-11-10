#pragma once
#include <algorithm>
#include "Player.h"

Player::Player(SDL_Rect pos/*, SDL_Rect img*/)
{
    pos_rect = pos;
    //img_rect = img;
    speed = 0;
    moving = false;
    h_direction = 1;
    v_direction = 0;
}
void Player::move_player(int time)
{
    int moved = 0;
    if (moving)
    {
        moved = std::min(time*(speed +(acceleration*time/2)/1000)/1000, max_speed_player*time/1000);
        pos_rect.x += (h_direction)*moved;
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
    }*/
    //plavno spirane
    else if (!moving && speed > 0)
    {

    }
    else
    {
        speed = 0;
    }
}

void Player::update(int time_passed, Key key, Type key_type)
{
    if ((key == UP || key == LEFT || key == RIGHT) && key_type == PRESSED)
    {
        moving = true;
        switch(key)
        {
            case UP:
            v_direction = 1;
            moving = false;
            break;
            case LEFT:
            h_direction = -1;
           // v_direction = 0;
            break;
            case RIGHT:
            h_direction = 1;
           // v_direction = 0;
            break;
            default: {}
        }
    }

    if (key_type == RELEASED) moving = false;

    move_player(time_passed);
}
