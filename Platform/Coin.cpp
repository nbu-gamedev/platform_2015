#include "Coin.h"

int Coin::taken_coins = 0;

Coin::Coin(SDL_Rect pos)
{
    pos_rect = pos;
    taken = false;
}

void Coin::update()
{
}

void Coin::render()
{
}
