#include "Actor.h"
Actor::~Actor()
{
}


void Actor::update()
{
}



// check if two actors' rectangles overlap
bool Actor::overlap(Actor* actor)
{
    if (pos_rect.x + pos_rect.w < actor -> pos_rect.x
        || pos_rect.x > actor -> pos_rect.x + actor -> pos_rect.w
        || pos_rect.y + pos_rect.h < actor -> pos_rect.y
        || pos_rect.y > actor -> pos_rect.y + actor -> pos_rect.h)

        return false;

    return true;
}

/*std::pair< std::pair<int,int>, std::pair<int,int> > Actor::getGridCoords()
{
    int i_beg_grid = pos_rect.y / TILE_SIZE; // pixel per tile
    int j_beg_grid = pos_rect.x / TILE_SIZE;
    int i_end_grid = ( pos_rect.y + pos_rect.h ) / TILE_SIZE;
    int j_end_grid = ( pos_rect.x + pos_rect.w ) / TILE_SIZE;

    return std::make_pair(std::make_pair(i_beg_grid,j_beg_grid),std::make_pair(i_end_grid,j_end_grid));
}*/

std::pair<int,int> Actor::get_grid_coords()
{
    int i = ( pos_rect.y + pos_rect.h / 2) / TILE_SIZE;
    int j = ( pos_rect.x + pos_rect.w / 2) / TILE_SIZE;

    return std::make_pair(i,j);
}
