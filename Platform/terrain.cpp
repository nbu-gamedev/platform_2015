#include "terrain.h"

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

void terrain::render()
{
	
}
