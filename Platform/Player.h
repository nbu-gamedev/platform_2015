#pragma once
#include "terrain.h"
#include "Enemy.h"
#include "Coin.h"
#include "Input_Handler.h"


const double max_speed_player = 300 * SCALE_FACTOR;
const double jump_start_speed = 530 * SCALE_FACTOR;
const double acceleration = 1000 * SCALE_FACTOR;
const double gravity_acceleration = 2200 * SCALE_FACTOR; // reach max height in about a second
const double terminal_velocity = 700 * SCALE_FACTOR;

class Player:public Actor
{
public:
    Player(SDL_Rect pos, std::vector<Actor*>** world);
    void update(int time_passed, Key_event* ke);
	void render(SDL_Renderer* renderer, int time_passed, CoreEngine &core);
    void check_collisions();
    //void render();
    void move_player(int time);
    void collide_with_terrain(terrain* terra);
  //  void collide_with_enemy(Enemy* enemy);
    void get_coin(Coin* coin);
    void die();
	void update_grid_pos();

	std::vector<Actor*>** grid;
    double real_x,real_y;
    int h_direction;
    int v_direction;
    double speed_y;
    bool moving;
    bool jumping;
    bool falling;
    bool alive;
    bool completely_dead;
    bool end_level;

    static int lives;
};
