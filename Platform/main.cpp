#ifdef __linux__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <SDL_image.h>
#include <iostream>
#include "World.h"
#include "Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"


using namespace std;



int main( int argc, char* args[] ) {

	World level;

	// The Game loop
	while (true)
	{
		// getTime(); (from SDL)
		// update();
		// render();


	}



	return 0;
}


