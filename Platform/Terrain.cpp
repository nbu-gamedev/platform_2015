#include "Terrain.h"
#include "CoreEngine.h"
Terrain::Terrain()
{
}

Terrain::Terrain(SDL_Rect rect, int i, int j, Object obj)
{
	pos_rect = rect;
	i_grid = i;
	j_grid = j;
	type = obj;
}

Terrain::~Terrain()
{
}

bool Terrain::update(int time_passed, Key_event* ke)
{
    return false;
}

void Terrain::render(SDL_Renderer* renderer, int time_passed, CoreEngine &core)
{

	SDL_RenderCopy(renderer, core.tiles_textures[type] , NULL, &pos_rect);
}
