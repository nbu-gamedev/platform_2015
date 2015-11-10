#pragma once
#include "Input_Handler.h"


InputHandler::InputHandler(){};

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
            result.k = (Key) event.key.keysym.sym;
        }

    }
    return result;
}
