#pragma once

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

const int animation_speed = 500*SCALE_FACTOR;
const int MENU_SIZE_W = 364*SCALE_FACTOR;
const int MENU_S_SIZE_H = 74*SCALE_FACTOR;
const int MENU_L_SIZE_H = 741*SCALE_FACTOR;

class Menu
{
public:
    static SDL_Texture* menu_opened;
    static SDL_Texture* menu_closed;
    SDL_Rect pos;
    double real_y;
    bool menu;
    bool animation;

    Menu ();

    void toggle_menu();

    void render_menu(SDL_Renderer * renderer, int time_passed, int direction);
};
