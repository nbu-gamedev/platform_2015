#include "Menu.h"
#include "Globals.h"

SDL_RenderCopy(renderer, core.player_textures[frame], NULL, &pos_rect);

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

}

// NOT TESTED AT ALL!!!!!!!!!!!!!!
void Menu::render_menu(SDL_Renderer * renderer, int time, int direction)
{
    if (!animation) return;

    double moved = time*animation_speed / 1000.;
    real_y += (-v_direction)*moved;
    pos.y = real_y;

    if ( pos_rect.y > M_WINDOW_HEIGHT)
    {
        menu = !menu;
    }

    else if( menu && real_y <  M_WINDOW_HEIGHT - MENU_L_SIZE_H)
    {
        pos_rect.y = real_y = M_WINDOW_HEIGHT - MENU_L_SIZE_H;
        animation = false;
    }
    else if( !menu && real_y <  M_WINDOW_HEIGHT - MENU_L_SIZE_H)
    {
        pos_rect.y = real_y = M_WINDOW_HEIGHT - MENU_S_SIZE_H;
        animation = false;
    }
}

void Menu::toggle_menu()
{
    animation = true;
}
