#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#include "CoreEngine.h"

int main( int argc, char* args[] ) {

	CoreEngine coreEngine;
	coreEngine.runGamingLoop();

	return 0;
}


