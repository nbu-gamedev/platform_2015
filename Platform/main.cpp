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



int main( int argc, char* args[] ) {

	World level;
	level.loadWorld("..\\Maps\\testmap.tmx");

	for (int i = 0; i < level.grid_height; i++)
	{
		for (int j = 0; j < level.grid_width; j++)
		{
			if (level.worldGrid[i][j] == NULL) cout << "0 ";
			else if (level.worldGrid[i][j]->loadedNumber == 0) cout << "1 ";
			else if (level.worldGrid[i][j]->loadedNumber == 1) cout << "2 ";
		}
		cout << endl;
	}

	// The Game loop
	while (true)
	{
		// getTime(); (from SDL)
		// update();
		// render();


	}



	return 0;
}


