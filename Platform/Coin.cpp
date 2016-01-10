#include "Coin.h"
#include "CoreEngine.h"

int Coin::coins_to_collect = 0;
int Coin::coins_number = 0;

Coin::Coin(SDL_Rect pos)
{
	pos_rect = pos;
	taken = false;
    last_rendered = 0;
    frame = 0;
}

bool Coin::update(int time_passed, Key_event* ke)
{
    return false;
}

void Coin::render(SDL_Renderer * renderer, int time_passed, CoreEngine & core)
{
	last_rendered += time_passed;
	if (last_rendered > 125)
	{
		frame++;
		frame %= core.coin_textures.size();
		last_rendered -= 125;
	}
	if (!taken)
	{
        SDL_RenderCopy(renderer, core.coin_textures[frame], NULL, &pos_rect);
    }
}
