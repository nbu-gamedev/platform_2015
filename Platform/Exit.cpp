#include "Exit.h"
#include "CoreEngine.h"


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
	return false;
}

void Exit::render(SDL_Renderer * renderer, int time_passed, CoreEngine & core)
{
	SDL_Rect door_top = pos_rect;
	door_top.y -= 60 * SCALE_FACTOR;
	SDL_RenderCopy(renderer, core.exit_textures[0], NULL, &pos_rect);
	SDL_RenderCopy(renderer, core.exit_textures[1], NULL, &door_top);
	SDL_Rect tmp = pos_rect;
	tmp.x -= 140 * SCALE_FACTOR;
	SDL_RenderCopy(renderer, core.exit_textures[0], NULL, &tmp);
}

