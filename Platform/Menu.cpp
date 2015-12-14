#include "Menu.h"
#include <iostream>
using namespace std;
SDL_Texture* Menu::menu_closed = NULL;
SDL_Texture* Menu::menu_opened = NULL;

Menu::Menu()
{
    pos.w = MENU_SIZE_W;
    pos.h = MENU_L_SIZE_H;
    pos.y = real_y = M_WINDOW_HEIGHT - MENU_L_SIZE_H;
    pos.x = (M_WINDOW_WIDTH - MENU_SIZE_W)/2;
    menu = true;
    animation = false;
    direction = 1;

}

// NOT TESTED AT ALL!!!!!!!!!!!!!!
void Menu::render_menu(SDL_Renderer * renderer, int time)
{
    SDL_RenderCopy(renderer, menu ? menu_opened : menu_closed, NULL, &pos);
}

void Menu::update(int time, Mouse_event* me)
{
    if (animation)
    {
        double moved = time*animation_speed / 1000.;
        real_y += (-direction)*moved;
        pos.y = real_y;

        if ( pos.y > M_WINDOW_HEIGHT)
        {
            menu = !menu;
            direction *= -1;
            pos.h = menu ? MENU_L_SIZE_H : MENU_S_SIZE_H;
        }

        else if( menu && real_y <  M_WINDOW_HEIGHT - MENU_L_SIZE_H)
        {
            pos.y = real_y = M_WINDOW_HEIGHT - MENU_L_SIZE_H;
            animation = false;
        }
        else if( !menu && real_y <  M_WINDOW_HEIGHT - MENU_S_SIZE_H)
        {
            pos.y = real_y = M_WINDOW_HEIGHT - MENU_S_SIZE_H;
            animation = false;
        }
    }
    else if (me)
    {
        if (point_inside_tr(menu ? toggle_points_l : toggle_points_s, me->x, me->y))
        {
            toggle_menu();
        }
    }
}

void Menu::toggle_menu()
{
    animation = true;
    direction *= -1;
}

bool point_inside_tr(int p[3][2], int x, int y){

    int a = (x-p[0][0])*(p[1][1] - p[0][1]) - (p[1][0] - p[0][0])*(y-p[0][1]);
    int b = (x-p[1][0])*(p[2][1] - p[1][1]) - (p[2][0] - p[1][0])*(y-p[1][1]);
    int c = (x-p[2][0])*(p[0][1] - p[2][1]) - (p[0][0] - p[2][0])*(y-p[2][1]);

    return ((a < 0 && b < 0 && c < 0) || (a > 0 && b > 0 && c > 0));
}
