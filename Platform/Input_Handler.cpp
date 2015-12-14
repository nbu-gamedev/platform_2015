#include "Input_Handler.h"

Custom_event
InputHandler::handle()
{
    Custom_event result;

    result.quit = false; // QUIT
    result.me = NULL;
    result.ke = NULL;

    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            result.quit = true;
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) //|| event.type == SDL_MOUSEBUTTONUP)
        {
            me.x = event.button.x;
            me.y = event.button.y;

            result.me = &me;
        }
         else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            const Uint8* key_state = SDL_GetKeyboardState(NULL);
            ke.jump_pressed = key_state[SDL_SCANCODE_UP] || key_state[SDL_SCANCODE_SPACE] || key_state[SDL_SCANCODE_W];
            ke.left_pressed = key_state[SDL_SCANCODE_LEFT] || key_state[SDL_SCANCODE_A];
            ke.right_pressed = key_state[SDL_SCANCODE_RIGHT] || key_state[SDL_SCANCODE_D];
            if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a))
            {
                ke.right_pressed = false;
            }
            else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d))
            {
                ke.left_pressed = false;
            }

            result.ke = &ke;
        }

    }
    return result;
}
