#pragma once
#include "terrain.h"
#include "Enemy.h"
#include "Coin.h"
#include "Input_Handler.h"


const int max_speed_player = 300 * SCALE_FACTOR;
const int jump_start_speed = 500 * SCALE_FACTOR;
const int max_acceleration = 400 * SCALE_FACTOR;
const int gravity_acceleration = 550 * SCALE_FACTOR; // reach max height in about a second


class Player:public Actor
{
public:
    Player(SDL_Rect pos);//, SDL_Rect& img);
    void update(Actor*** grid, int time_passed, Key key, Type key_type);
    void check_collisions(Actor*** grid);
    //void render();
    void move_player(int time);
    void collide_with_terrain(terrain* terra);
  //  void collide_with_enemy(Enemy* enemy);
    void get_coin(Coin* coin);
    void die();

    double real_x,real_y;
    int h_direction;
    int v_direction;
    int speed_y;
    bool moving;
    bool jumping;
    bool falling;
    int acceleration;
    bool alive;
};
