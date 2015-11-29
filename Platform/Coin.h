#pragma once

#include "Actor.h"

class Coin : public Actor
{
public:

    Coin(SDL_Rect pos);
    void update();
    virtual void update(Actor*** grid, int time_passed, Key key, Type key_type) {};
    void render();

    static int taken_coins;
    bool taken;
};
