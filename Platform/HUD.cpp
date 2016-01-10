#include "HUD.h"
#include "Globals.h"
#define START_X 12
#define START_Y 12

SDL_Texture* Hud::digits[10] = {};
SDL_Texture* Hud::coin_icon = NULL;
SDL_Texture* Hud::heart_empty = NULL;
SDL_Texture* Hud::heart_full = NULL;

Hud::Hud()
{
    space = 5*SCALE_FACTOR;
    size_element_x = 35*SCALE_FACTOR;
    size_element_y = 38*SCALE_FACTOR;
    pos.x = pos.y = START_X*SCALE_FACTOR;
    pos.w = size_element_x;
    pos.h = size_element_y;
}

void Hud::render(SDL_Renderer* renderer)
{
    pos.x = START_X;
    pos.y = START_Y;
    int full_hearts = Player::lives;
    int empty_hearts = 3 - full_hearts;
    while (full_hearts--)
    {
        SDL_RenderCopy(renderer, heart_full , NULL, &pos);
        pos.x += space + size_element_x;
    }
    while (empty_hearts--)
    {
        SDL_RenderCopy(renderer, heart_empty , NULL, &pos);
        pos.x += space + size_element_x;
    }

    pos.x = START_X;
    pos.y += space + size_element_y;
    SDL_RenderCopy(renderer, coin_icon , NULL, &pos);

    int coins = Coin::coins_number - Coin::coins_to_collect;

    while(coins)
    {
        digs.push(coins%10);
        coins /= 10;
    }
    if (digs.empty())
    {
        digs.push(0);
    }
    while(!digs.empty())
    {
        pos.x += size_element_x;
        SDL_RenderCopy(renderer, digits[digs.top()] , NULL, &pos);
        digs.pop();
    }

}
