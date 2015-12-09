#include "Actor.h"
Actor::~Actor()
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

std::pair<int,int> Actor::get_grid_coords()
{
    int i = ( pos_rect.y + pos_rect.h / 2) / TILE_SIZE;
    int j = ( pos_rect.x + pos_rect.w / 2) / TILE_SIZE;

    return std::make_pair(i,j);
}
