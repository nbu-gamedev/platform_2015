#include "Actor.h"

Actor::~Actor()
{
}

void Actor::update()
{
}

void Actor::render()
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

std::pair< std::pair<int,int>, std::pair<int,int> > Actor::getGridCoords()
{
    int i_beg_grid = pos_rect.y / 70; // pixel per tile
    int j_beg_grid = pos_rect.x / 70;
    int i_end_grid = ( pos_rect.y + pos_rect.h ) / 70;
    int j_end_grid = ( pos_rect.x + pos_rect.w ) / 70;

    return std::make_pair(std::make_pair(i_beg_grid,j_beg_grid),std::make_pair(i_end_grid,j_end_grid));
}
