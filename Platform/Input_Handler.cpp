#include "Input_Handler.h"


InputHandler::InputHandler()
{
    // map all player' keys
    keys[SDLK_UP] = keys[SDLK_SPACE] = keys[SDLK_w] = JUMP;
    keys[SDLK_LEFT] = keys[SDLK_a] = LEFT;
    keys[SDLK_RIGHT] = keys[SDLK_d] = RIGHT;
}

Custom_Event InputHandler::handle()
{
    Custom_Event result{(Source_Type)0,(Key)0,(Type)0};
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            result.src = QUIT;
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
        {
            result.src = MOUSE;
        }
         else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            result.src = KEY;
            result.tp = event.type == SDL_KEYDOWN ? PRESSED : RELEASED;
            auto k = keys.find(event.key.keysym.sym);
            result.k = k != keys.end() ? k->second : NO_KEY;
        }

    }
    return result;
}
