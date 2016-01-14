#pragma once
#include "Terrain.h"
#include "Enemy.h"
#include "Coin.h"
#include "Input_Handler.h"
//

//
const double max_speed_player = 300 * SCALE_FACTOR;
const double jump_start_speed = 630 * SCALE_FACTOR;
const double acceleration = 1000 * SCALE_FACTOR;
const double gravity_acceleration = 1250 * SCALE_FACTOR; // reach max height in about a second
const double terminal_velocity = 700 * SCALE_FACTOR;

class Player:public Actor
{
public:
    Player(SDL_Rect pos, std::vector<Actor*>** world);
    bool update(int time_passed, Key_event* ke);
	void render(SDL_Renderer* renderer, int time_passed, CoreEngine &core);
    void check_collisions();
    //void render();
    void move_player(int time);
    void collide_with_Terrain(Terrain* terra);
    void collide_with_enemy(Enemy* enemy);
    void get_coin(Coin* coin);
    void die();
	bool update_grid_pos();
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

	//yavor test sound must be size of enum
	bool sound_events_to_play[5];
	void play_sound(CoreEngine &core);
	//
    static int lives;
};
