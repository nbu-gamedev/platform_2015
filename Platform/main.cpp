#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <iostream>
#include "World.h"
#include "Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"

#include <ctime>

using namespace std;

int main( int argc, char* args[] ) {

	World level;
	SDL_Rect pos{3,3,33,33};
	SDL_Rect posIm{0,0,30,30};
	Player* player = new Player(pos);
	bool game_running = true;
	SDL_Event event;
	int key = 0;
	bool key_type = false;

    SDL_Init( SDL_INIT_EVERYTHING );
	SDL_Window* window = SDL_CreateWindow("WIN", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 1000, 500, SDL_WINDOW_SHOWN);
	SDL_Surface* sc = SDL_GetWindowSurface(window);
	SDL_Surface* pl = SDL_LoadBMP( "pl.bmp" );

    time_t timer, curr;
    time(&timer);

	// The Game loop
	while (game_running)
	{
        time(&curr);
        cout<< difftime(curr,timer) << endl;
        timer = curr;
        while(SDL_PollEvent(&event))
        {
            //if (event.type == SDL_KEYUP) printf("key released\n");
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F4))
            {
                game_running = false;
            }
            else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
            {
                key = (int)event.key.keysym.sym;
                key_type = event.type == SDL_KEYDOWN ? 1:0;
            }
        }

		// getTime(); (from SDL)
		//update();
        player->update(300, key, key_type);

        SDL_BlitSurface( pl, NULL, sc, &player->pos_rect );
        SDL_UpdateWindowSurface( window );
		// render();

	}

    SDL_FreeSurface(pl);
    SDL_FreeSurface(sc);
    SDL_DestroyWindow(window);
    SDL_Quit();

	return 0;
}


