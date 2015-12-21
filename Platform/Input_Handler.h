#pragma once
#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#else
#include <SDL_keyboard.h>
#include <SDL_events.h>
#endif

struct Key_event
{
    bool jump_pressed;
    bool left_pressed;
    bool right_pressed;
};

struct Mouse_event
{
    bool clicked;
    int x;
    int y;
};

struct Custom_event
{
    Mouse_event* me;
    Key_event* ke;
};

class InputHandler
{
    SDL_Event event;

public:

    Mouse_event me;
    Key_event ke;

    Custom_event handle();

};
