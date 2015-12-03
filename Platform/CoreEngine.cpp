#include "CoreEngine.h"

#include <iostream>

CoreEngine::CoreEngine()
{
	gWindow = NULL;
	gRenderer = NULL;

	//gScreenSurface = NULL;
	//gPNGSurface = NULL;
}

bool CoreEngine :: init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow(M_WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, M_WINDOW_WIDTH, M_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool CoreEngine::loadMedia()
{
	//Loading success flag
	bool success = true;

	// load player files
	std::string path = "Art/platformerArt/png/character/walk/walk0001.png";
	int index = path.size() - 5;
	char counter = '1';
	for (int i = 0; i < 11; ++i)
	{
		path[index] = counter;
		player_textures.push_back(loadTexture(path));
		if (player_textures[i] == NULL)
		{
			printf("Failed to load texture image!\n");
			success = false;
		}
		counter++;
		if (counter > '9')
		{
			counter = '0';
			path[index - 1]++;
		}
	}

	//Loading tiles
	path = "Art/platformerArt/png/ground.png";
	tiles_textures.push_back(loadTexture(path));
	if ( tiles_textures.back() == NULL)
	{
		printf("Failed to load tile image!\n");
		success = false;
	}

	path = "Art/platformerArt/png/ground_dirt.png";
	tiles_textures.push_back(loadTexture(path));
	if (tiles_textures.back() == NULL)
	{
		printf("Failed to load tile image!\n");
		success = false;
	}

	//load enemy files

	path = "Art/platformerArt/png/enemies/slime_normal.png";

	enemy_textures.push_back(loadTexture(path));
	if (tiles_textures.back() == NULL)
	{
		printf("Failed to load tile image!\n");
		success = false;
	}
	path = "Art/platformerArt/png/enemies/slime_walk.png";

	enemy_textures.push_back(loadTexture(path));
	if (tiles_textures.back() == NULL)
	{
		printf("Failed to load tile image!\n");
		success = false;
	}
	path = "Art/platformerArt/png/enemies/slime_dead.png";

	enemy_textures.push_back(loadTexture(path));
	if (tiles_textures.back() == NULL)
	{
		printf("Failed to load tile image!\n");
		success = false;
	}
	// load coins
	path = "Art/platformerArt/png/coin_bronze.png";

	coin_textures.push_back(loadTexture(path));
	if (coin_textures.back() == NULL)
	{
		printf("Failed to load tile image!\n");
		success = false;
	}
	path = "Art/platformerArt/png/coin_silver.png";

	coin_textures.push_back(loadTexture(path));
	if (coin_textures.back() == NULL)
	{
		printf("Failed to load tile image!\n");
		success = false;
	}
	path = "Art/platformerArt/png/coin_gold.png";

	coin_textures.push_back(loadTexture(path));
	if (coin_textures.back() == NULL)
	{
		printf("Failed to load tile image!\n");
		success = false;
	}

	return success;
}

void CoreEngine::close()
{
	//Free loaded image player
	for (int i = 0; i < player_textures.size(); ++i)
	{
		SDL_DestroyTexture(player_textures[i]);
		player_textures[i] = NULL;
	}

	//free tiles;
	for (int i = 0; i < tiles_textures.size() ; ++i)
	{
		SDL_DestroyTexture(tiles_textures[i]);
		tiles_textures[i] = NULL;
	}
	//free enemies
	for (int i = 0; i < enemy_textures.size(); ++i)
	{
		SDL_DestroyTexture(enemy_textures[i]);
		enemy_textures[i] = NULL;
	}
	//free coins
	for (int i = 0; i < coin_textures.size(); ++i)
	{
		SDL_DestroyTexture(coin_textures[i]);
		coin_textures[i] = NULL;
	}
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;


	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* CoreEngine::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

void CoreEngine::runGamingLoop()
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		// TODO maybe wrap into class
		// NOTE-SAMIR: Create new world for each new level to clear data from previous level.
		if (!m_world.loadWorld("../Maps/testmap.tmx"))
		{
			std::cout << "Error loading map !!" << std::endl;
		}
		else
			{

			//Load media
			if (!loadMedia())
			{
				printf("Failed to load media!\n");
			}
			else
			{


				bool game_running = true;
				//TODO yavor  move this
				SDL_Rect tile;
				tile.h = m_world.loadedObjects[0].height;
				tile.w = m_world.loadedObjects[0].width;
				// Get time
				int prev_time, curr_time, time_passed;
				prev_time = SDL_GetTicks();

				InputHandler handler;
				Custom_event ce;
				// The Game loop
				while (game_running)
				{
					curr_time = SDL_GetTicks();
					time_passed = curr_time - prev_time;
					if (time_passed < 15)
					{
						continue;
					}

					prev_time = curr_time;
					ce = handler.handle();

					if (ce.quit) game_running = false;
					//update();

					//Clear screen
					SDL_RenderClear(gRenderer);

					//Render Tiles to screen
					for (int i = 0; i <  m_world.grid_height; ++i)
					{
						for (int y = 0; y < m_world.grid_width; ++y)
						{
							if (m_world.worldGrid[i][y] != NULL)
							{
								m_world.worldGrid[i][y]->update(time_passed, ce.ke);
								m_world.worldGrid[i][y]->render(gRenderer, time_passed, *this);

							}
						}
					}




					//Update screen
					SDL_RenderPresent(gRenderer);
					//SDL_Delay(33);

				}
			}
		}
	}

	//Free resources and close SDL
	close();

}
