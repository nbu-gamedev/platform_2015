#pragma once

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <stack>
#include "Player.h"
#include "Coin.h"

class Hud
{
public:
    static SDL_Texture* digits[10];
    static SDL_Texture* coin_icon;
    static SDL_Texture* heart_full;
    static SDL_Texture* heart_empty;
    int size_element_x;
    int space;
    std::stack<int> digs;
    SDL_Rect pos;

    Hud();
    void render(SDL_Renderer* renderer);

};
