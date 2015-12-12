#include "Coin.h"
#include "CoreEngine.h"

int Coin::coins_to_collect = 0;

Coin::Coin(SDL_Rect pos)
{
	pos_rect = pos;
	taken = false;
}

bool Coin::update(int time_passed, Key_event* ke)
{
    return false;
}

void Coin::render(SDL_Renderer * renderer, int time_passed, CoreEngine & core)
{
	/*
	static SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
	static int lastUpdated = 0;
	static int frame = 0;
	lastUpdated += time_passed;
	if (lastUpdated > 1000)
	{
		frame++;
		frame %= core.enemy_textures.size();
		lastUpdated -= 1000;
	}
	
		if (direction < 0)
		{
			SDL_RenderCopy(renderer, core.enemy_textures[frame], NULL, &pos_rect);
			
		}
		else
		{
			SDL_RenderCopyEx(renderer, core.enemy_textures[frame], NULL, &pos_rect, 180.0f, NULL, flip);
		}
	*/
	static int lastUpdated = 0;
	static int frame = 0;
	lastUpdated += time_passed;
	if (lastUpdated > 4200)
	{
		frame++;
		frame %= core.coin_textures.size();
		lastUpdated -= 4200;
	}
	if (!taken)
	{
        SDL_RenderCopy(renderer, core.coin_textures[frame], NULL, &pos_rect);
    }
}
