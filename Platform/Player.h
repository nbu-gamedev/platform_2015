#pragma once
#include "Actor.h"
#include "Input_Handler.h"

const int max_speed_player = 180; // TO BE CHANGED
const int max_jump_height = 430; // TO BE CHANGED

const int acceleration = 400; // TO BE CHANGED

class Player:public Actor
{
public:
    Player(SDL_Rect pos);//, SDL_Rect& img);
    void update(int time_passed, Key key, Type key_type);

    //void render();
    void move_player(int time);
    void check_collisions();
    std::pair<int,int> getGridCoords();

    float real_x,real_y;
    int h_direction;
    int v_direction;
    bool moving;
    int jump_height;
};
