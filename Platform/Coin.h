#pragma once

#include "Actor.h"

class Coin : public Actor
{
public:

    Coin(SDL_Rect pos);
    void update();
    virtual void update(Actor*** grid, int time_passed, Key key, Type key_type) {};
	void render(SDL_Renderer * renderer, int time_passed, CoreEngine & core);

    static int taken_coins;
    bool taken;
};
