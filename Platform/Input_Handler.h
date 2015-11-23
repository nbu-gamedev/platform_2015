#pragma once
#ifdef __linux__
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_events.h>
#else
#include <SDL_keyboard.h>
#include <SDL_events.h>
#endif

#include <map>

enum Key {NO_KEY, JUMP, RIGHT, LEFT};
enum Source_Type {NO_SOURCE_TYPE, MOUSE, KEY, QUIT};
enum Type {NO_TYPE,PRESSED, RELEASED};

struct Custom_Event
{
    Source_Type src;
    Key k;
    Type tp;
};

class InputHandler
{
    std::map<SDL_Keycode,Key> keys;
    SDL_Event event;
public:

    InputHandler();

    Custom_Event handle();

};
