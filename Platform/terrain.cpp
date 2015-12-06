#include "terrain.h"
#include "CoreEngine.h"
terrain::terrain()
{
}

terrain::terrain(SDL_Rect rect, int i, int j, Object obj)
{
	pos_rect = rect;
	i_grid = i;
	j_grid = j;
	type = obj;
}

terrain::~terrain()
{
}

void terrain::update()
{
}

void terrain::render(SDL_Renderer* renderer, int time_passed, CoreEngine &core)
{

	SDL_RenderCopy(renderer, core.tiles_textures[type] , NULL, &pos_rect);
}
