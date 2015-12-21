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

const int animation_speed = 3000*SCALE_FACTOR;
const int MENU_SIZE_W = 353*SCALE_FACTOR;
const int MENU_S_SIZE_H = 74*SCALE_FACTOR;
const int MENU_L_SIZE_H = 849*SCALE_FACTOR;

// position on the menu
static int relative_y[6] = {27*SCALE_FACTOR, 76*SCALE_FACTOR, 228*SCALE_FACTOR, 339*SCALE_FACTOR, 450*SCALE_FACTOR, 610*SCALE_FACTOR};

// sizes of buttons
static int btns_sizes[6][2] = {
                                    {63*SCALE_FACTOR,35*SCALE_FACTOR},
                                    {124*SCALE_FACTOR,69*SCALE_FACTOR},
                                    {167*SCALE_FACTOR,75*SCALE_FACTOR},
                                    {167*SCALE_FACTOR,75*SCALE_FACTOR},
                                    {167*SCALE_FACTOR,75*SCALE_FACTOR},
                                    {106*SCALE_FACTOR,57*SCALE_FACTOR}
};

class Button;

bool point_inside_tr(int p[3][2], int x, int y);

class Menu
{
public:
    static SDL_Texture* menu_opened;
    static SDL_Texture* menu_closed;
    static SDL_Texture* btns_images[6][2];
    SDL_Rect pos;
    double real_y;
    bool menu;
    bool animation;
    int direction;
    Button* children[6];
    Menu ();
    ~Menu();

    void toggle_menu();
    void update(int time, Mouse_event* me);
    void render_menu(SDL_Renderer * renderer);
};

class Button
{
public:
    int type; //triangle ot rectangle
    int num;
    SDL_Rect pos;
    int points[3][2];
    bool selected;

    Button(int type, int number);
    bool update(int x, int y);
    void render(SDL_Renderer * renderer);
};
