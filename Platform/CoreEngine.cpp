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

	//Load PNG texture
	gTexture = loadTexture("Art/platformerArt/png/character/walk/walk0001.png");
	if (gTexture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}

void CoreEngine::close()
{
	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

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
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			World world;   //TODO maybe wrap into class
			if (!world.loadWorld("../Maps/testmap.tmx"))
			{
				std::cout << "Error loading map !!" << std::endl;
			}
			else
			{

				SDL_Rect pos{ 0,M_WINDOW_HEIGHT - 100,70,100 };
				Player* player = new Player(pos);
				bool game_running = true;

				// Get time
				int prev_time, curr_time, time_passed;
				prev_time = SDL_GetTicks();

                InputHandler handler;
                Custom_Event ce;
				// The Game loop
				while (game_running)
				{
					curr_time = SDL_GetTicks();
					time_passed = curr_time - prev_time;
					prev_time = curr_time;
					ce = handler.handle();

                    if (ce.src == QUIT) game_running = false;
					//update();
					player->update(time_passed, ce.k, ce.tp);

					//Clear screen
					SDL_RenderClear(gRenderer);

					//Render texture to screen
					SDL_RenderCopy(gRenderer, gTexture, NULL, &player->pos_rect);

					//Update screen
					SDL_RenderPresent(gRenderer);
					SDL_Delay(33);
				}
			}
		}
	}

	//Free resources and close SDL
	close();

}
