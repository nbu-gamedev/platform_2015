#include "Exit.h"
#include "CoreEngine.h"
#include "Coin.h"


Exit::Exit(SDL_Rect rect, int i, int j)
{
	pos_rect = rect;
	i_grid = i;
	j_grid = j;

}


Exit::~Exit()
{
}

bool Exit::update(int time_passed, Key_event * ke)
{
	if (Coin::coins_to_collect == 0)
	{
		open = true;
	}
	return false;
}

void Exit::render(SDL_Renderer * renderer, int time_passed, CoreEngine & core)
{
	SDL_Rect door_top = pos_rect;
	door_top.y -= 60 * SCALE_FACTOR;
	if (!open)
	{
		SDL_RenderCopy(renderer, core.exit_textures[0], NULL, &pos_rect);
		SDL_RenderCopy(renderer, core.exit_textures[1], NULL, &door_top);
	}
	else
	{
		SDL_RenderCopy(renderer, core.exit_textures[2], NULL, &pos_rect);
		SDL_RenderCopy(renderer, core.exit_textures[3], NULL, &door_top);
	}
	
}

