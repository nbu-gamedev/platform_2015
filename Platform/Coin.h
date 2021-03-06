#pragma once

#include "Actor.h"

class Coin : public Actor
{
public:

    Coin(SDL_Rect pos);
    bool update(int time_passed, Key_event* ke);
	void render(SDL_Renderer * renderer, int time_passed, CoreEngine & core);

    static int coins_to_collect;
    static int coins_number;
    bool taken;
};
