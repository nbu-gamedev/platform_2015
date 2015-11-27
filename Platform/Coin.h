#pragma once

#include "Actor.h"

class Coin : public Actor
{
public:

    Coin(SDL_Rect pos);
    void update();
    void render();

    static int taken_coins;
    bool taken;
};
