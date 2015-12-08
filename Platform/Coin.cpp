#include "Coin.h"
#include "CoreEngine.h"

int Coin::coins_to_collect = 0;

Coin::Coin(SDL_Rect pos)
{
	pos_rect = pos;
	taken = false;
}

void Coin::update()
{
}

void Coin::render(SDL_Renderer * renderer, int time_passed, CoreEngine & core)
{
	if (!taken)
	{
        SDL_RenderCopy(renderer, core.coin_textures[2], NULL, &pos_rect);
    }
}
