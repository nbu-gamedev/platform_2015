#include "CoreEngine.h"
#include <iostream>

CoreEngine::CoreEngine()
{
	gWindow = NULL;
	gScreenSurface = NULL;
	gPNGSurface = NULL;
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
		//Create window
		gWindow = SDL_CreateWindow(M_WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, M_WINDOW_WIDTH, M_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				success = false;
			}
			else
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}

	return success;
}

bool CoreEngine::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG surface
	gPNGSurface = loadSurface("Art/platformerArt/png/character/walk/walk0001.png");   // temp art
	if (gPNGSurface == NULL)
	{
		printf("Failed to load PNG image!\n");
		success = false;
	}

	return success;
}

void CoreEngine::close()
{
	//Free loaded image
	SDL_FreeSurface(gPNGSurface);
	gPNGSurface = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* CoreEngine::loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
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
            SDL_Rect pos{0,M_WINDOW_HEIGHT-100,70,100};
            Player* player = new Player(pos);
            bool game_running = true;
            SDL_Event event;
            int key = 0;
            bool key_type = false;

            // Get time
            int prev_time, curr_time, time_passed;
            prev_time = SDL_GetTicks();

            // The Game loop
            while (game_running)
            {
                curr_time = SDL_GetTicks();
                time_passed = curr_time - prev_time;
                prev_time = curr_time;
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

                //update();
                player->update(time_passed, key, key_type);

				//Apply the PNG image
				SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, &player->pos_rect);

				//Update the surface
				SDL_UpdateWindowSurface(gWindow);
				SDL_Delay(100);
			}
		}
	}

	//Free resources and close SDL
	close();

}
