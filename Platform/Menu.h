#pragma once

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#include "Globals.h"
#include "Input_Handler.h"

const int animation_speed = 1300*SCALE_FACTOR;
const int MENU_SIZE_W = 343*SCALE_FACTOR;
const int MENU_S_SIZE_H = 74*SCALE_FACTOR;
const int MENU_L_SIZE_H = 849*SCALE_FACTOR;

//poins of triangle (toggle menu) buttons
static int toggle_points_l[3][2] = {
                                    {133*SCALE_FACTOR + (M_WINDOW_WIDTH - MENU_SIZE_W)/2, 46*SCALE_FACTOR + M_WINDOW_HEIGHT - MENU_L_SIZE_H},
                                    {250*SCALE_FACTOR + (M_WINDOW_WIDTH - MENU_SIZE_W)/2, 46*SCALE_FACTOR + M_WINDOW_HEIGHT - MENU_L_SIZE_H},
                                    {189*SCALE_FACTOR + (M_WINDOW_WIDTH - MENU_SIZE_W)/2, 113*SCALE_FACTOR + M_WINDOW_HEIGHT - MENU_L_SIZE_H}
                                };
static int toggle_points_s[3][2] = {
                                    {183*SCALE_FACTOR + (M_WINDOW_WIDTH - MENU_SIZE_W)/2, 22*SCALE_FACTOR + M_WINDOW_HEIGHT - MENU_S_SIZE_H},
                                    {153*SCALE_FACTOR + (M_WINDOW_WIDTH - MENU_SIZE_W)/2, 60*SCALE_FACTOR + M_WINDOW_HEIGHT - MENU_S_SIZE_H},
                                    {215*SCALE_FACTOR + (M_WINDOW_WIDTH - MENU_SIZE_W)/2, 60*SCALE_FACTOR + M_WINDOW_HEIGHT - MENU_S_SIZE_H}
                                };

bool point_inside_tr(int p[3][2], int x, int y);

class Menu
{
public:
    static SDL_Texture* menu_opened;
    static SDL_Texture* menu_closed;
    SDL_Rect pos;
    double real_y;
    bool menu;
    bool animation;
    int direction;
    Menu ();

    void toggle_menu();
    void update(int time, Mouse_event* me);
    void render_menu(SDL_Renderer * renderer, int time_passed);
};
