#include "CoreEngine.h"

#include <iostream>
#include <fstream>
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
	
	//Open image config file
	ifstream input_file;
	string path, line;
	int num_of_textures;
	//Load images
	input_file.open("Config/configImage.txt");
	if(!input_file.is_open())
	{
		cout << "Couldn't open image config file !!" << endl;
	}
	else
	{
		while (getline(input_file, line))
		{
			//Load player texture
			if (line == "player")
			{
				input_file >> num_of_textures;
				getline(input_file, path);
				for (int i = 0; i < num_of_textures - 2; ++i) // -2 , because one is for jump and one is for dead
				{
					getline(input_file, path);
					player_textures.push_back( loadTexture(path));
					if (player_textures[i] == NULL)
					{
						printf("Failed to load texture image!\n");
						success = false;
					}
				}
				getline(input_file, path);
				player_jump_texture = loadTexture(path);
				if (player_jump_texture == NULL)
				{
					printf("Failed to load texture image!\n");
					success = false;
				}
				getline(input_file, path);
				player_dead_texture = loadTexture(path);
				if (player_dead_texture == NULL)
				{
					printf("Failed to load texture image!\n");
					success = false;
				}
			}
			//Load tile textures
			else if (line == "tiles")
			{
				input_file >> num_of_textures;
				getline(input_file, path);
				for (int i = 0; i < num_of_textures; ++i)
				{
					getline(input_file, path);
					tiles_textures.push_back(loadTexture(path));
					if (tiles_textures[i] == NULL)
					{
						printf("Failed to load texture image!\n");
						success = false;
					}
				}
			}
			//Load enemy textures
			else if (line == "enemy")
			{
				input_file >> num_of_textures;
				getline(input_file, path);
				for (int i = 0; i < num_of_textures - 1; ++i)  // 1 is reserved for dead texture
				{
					getline(input_file, path);
					enemy_textures.push_back(loadTexture(path));
					if (enemy_textures[i] == NULL)
					{
						printf("Failed to load texture image!\n");
						success = false;
					}
				}
				getline(input_file, path);
				enemy_dead_texture = loadTexture(path);
				if (enemy_dead_texture == NULL)
				{
					printf("Failed to load texture image!\n");
					success = false;
				}
			}
			//Load coins
			else if (line == "coin")
			{
				input_file >> num_of_textures;
				getline(input_file, path);
				for (int i = 0; i < num_of_textures; ++i)
				{
					getline(input_file, path);
					coin_textures.push_back(loadTexture(path));
					if (coin_textures[i] == NULL)
					{
						printf("Failed to load texture image!\n");
						success = false;
					}
				}
			}
			//Load background
			else if (line == "background")
			{
				getline(input_file, path);
				background_texture = loadTexture(path);
				if (background_texture == NULL)
				{
					printf("Failed to load texture image!\n");
					success = false;
				}
			}
			else if (line == "exit")
			{
				input_file >> num_of_textures;
				getline(input_file, path);
				for (int i = 0; i < num_of_textures; ++i)
				{
					getline(input_file, path);
					exit_textures.push_back(loadTexture(path));
					if (exit_textures[i] == NULL)
					{
						printf("Failed to load texture image!\n");
						success = false;
					}
				}
			}
		}
		input_file.close();
	}
	return success;
}

void CoreEngine::close()
{
	//Free background 
	SDL_DestroyTexture(background_texture);
	background_texture = NULL;

	//Free loaded image player
	for (int i = 0; i < player_textures.size(); ++i)
	{
		SDL_DestroyTexture(player_textures[i]);
		player_textures[i] = NULL;
	}
	SDL_DestroyTexture( player_dead_texture);
	player_dead_texture = NULL;

	SDL_DestroyTexture( player_jump_texture);
	player_jump_texture = NULL;

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
	SDL_DestroyTexture(enemy_dead_texture);
	enemy_dead_texture = NULL;
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
		if (!m_world.loadWorld("../Maps/testmap - Copy.tmx"))
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
				bool deletion = false;
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

					if (ce.quit || (m_world.player -> completely_dead && !Player::lives)) game_running = false;

                    //respawn if neccessary
                    if (m_world.player -> completely_dead)
                    {
                        m_world.respawn();
                    }

					//Clear screen
					SDL_RenderClear(gRenderer);
					
					//Render background
					SDL_RenderCopy(gRenderer, background_texture, NULL, NULL);
				
					//Render Tiles to screen
					for (int i = 0; i <  GRID_HEIGHT; ++i)
					{
						for (int y = 0; y < GRID_WIDTH; ++y)
						{
                             for (int k = 0; k < m_world.worldGrid[i][y].size();)
							{
                                Actor* actor = m_world.worldGrid[i][y][k];
								deletion = actor->update(time_passed, ce.ke);
								if (actor->type != PLAYER)
								{
									actor->render(gRenderer, time_passed, *this);
								}
                                if (!deletion) k++;
							}
						}
					}
					m_world.player->render(gRenderer, time_passed, *this);

					//Update screen
					SDL_RenderPresent(gRenderer);

				}
			}
		}
	}

	//Free resources and close SDL
	close();

}
