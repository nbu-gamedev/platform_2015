#include "Input_Handler.h"
#include "Globals.h"

Custom_event
InputHandler::handle()
{
    Custom_event result;

    result.me = NULL;
    result.ke = NULL;

    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            GAME_RUNNING = false;
        }
        else if(event.type == SDL_MOUSEMOTION)
        {
            me.clicked = false;
            me.x = event.motion.x;
            me.y = event.motion.y;

            result.me = &me;
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            me.clicked = true;
            me.x = event.button.x;
            me.y = event.button.y;

            result.me = &me;
        }
         else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            const Uint8* key_state = SDL_GetKeyboardState(NULL);
            ke.jump_pressed = key_state[SDL_SCANCODE_UP] || key_state[SDL_SCANCODE_SPACE] || key_state[SDL_SCANCODE_W];
            if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a))
            {
                ke.left_pressed = true;
                ke.right_pressed = false;
            }
            else if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d))
            {
                ke.right_pressed = true;
                ke.left_pressed = false;
            }
            if (event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a))
            {
                ke.left_pressed = false;
                ke.right_pressed = key_state[SDL_SCANCODE_RIGHT] || key_state[SDL_SCANCODE_D];

            }
            else if (event.type == SDL_KEYUP && (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d))
            {
                ke.right_pressed = false;
                ke.left_pressed = key_state[SDL_SCANCODE_LEFT] || key_state[SDL_SCANCODE_A];
            }
            result.ke = &ke;
        }

    }
    return result;
}
