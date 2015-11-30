#include "terrain.h"
#include "CoreEngine.h"
terrain::terrain()
{
}

terrain::terrain(SDL_Rect rect, Object obj)
{
	pos_rect = rect;
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
