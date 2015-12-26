#include "CoreEngine.h"
#include "Menu.h"

#include <iostream>
#include <fstream>
#include "SoundEvents.h"
#include "Sound.h"
CoreEngine::CoreEngine()
{
	gWindow = NULL;
	gRenderer = NULL;
	current_level = 0;
	//gScreenSurface = NULL;
	//gPNGSurface = NULL;
}

bool CoreEngine :: init()
{
	//Initialization flag
	bool success = true;


	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
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
				//Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
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
		cout << "Couldn't open image configImage file !!" << endl;
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
			//Load menu images
			else if (line == "menu")
			{
				getline(input_file, path);
				Menu::menu_opened = loadTexture(path);
                if (Menu::menu_opened == NULL)
                {
                    printf("Failed to load menu texture image!\n");
                    success = false;
                }
                getline(input_file, path);
				Menu::menu_closed = loadTexture(path);
                if (Menu::menu_closed == NULL)
                {
                    printf("Failed to load menu texture image!\n");
                    success = false;
                }
			}
			else if (line == "buttons")
			{
                input_file >> num_of_textures;
				getline(input_file, path);
				for (int i = 0; i < num_of_textures; i++)
				{
					getline(input_file, path);
					Menu::btns_images[i/2][i%2] = loadTexture(path);
					if (Menu::btns_images[i/2][i%2] == NULL)
					{
						printf("Failed to load button image!\n");
						success = false;
					}
				}
			}
		}
		input_file.close();
	}
	// Load sound
	input_file.open("Config/configSound.txt");
	if (!input_file.is_open())
	{
		cout << "Couldn't open image configSound file !!" << endl;
	}
	else
	{
		while (getline(input_file, line))
		{
			if ( line == "coin" || line == "jump" || line == "dead" || line == "colision" || line == "exit")
			{
				getline(input_file, path);
				sound_effects.push_back(Mix_LoadWAV(path.c_str()));
				if (sound_effects.back() == NULL)
				{
					printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
			else if (line == "music")
			{
				getline(input_file, path);
				music_loops.push_back(Mix_LoadMUS(path.c_str()));
				if (music_loops.back() == NULL)
				{
					printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
		input_file.close();
	}


	return success;
}

bool CoreEngine::loadLevels(string levels)
{
	ifstream input_file;
	string path, line;
	int num_of_textures;
	//Load images
	input_file.open(levels);
	if (!input_file.is_open())
	{
		cout << "Couldn't open levels configImage file !!" << endl;
		return false;
	}
	else
	{
		while (getline(input_file, line))
		{
			cout << "1: " << line << endl;
			level_path.push_back(line);
		}
	}
	return true;
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
	//free menu
	SDL_DestroyTexture(Menu::menu_closed);
	SDL_DestroyTexture(Menu::menu_opened);
	Menu::menu_closed = Menu::menu_opened = NULL;
	for (int i = 0; i < 6; ++i)
	{
		SDL_DestroyTexture(Menu::btns_images[i][0]);
		SDL_DestroyTexture(Menu::btns_images[i][1]);
		Menu::btns_images[i][0] = Menu::btns_images[i][1] = NULL;
	}
	// free sounds
	for (int i = 0; i < sound_effects.size(); ++i)
	{

		Mix_FreeChunk( sound_effects[i] );
		sound_effects[i] = NULL;
	}
	// free music
	for (int i = 0; i < music_loops.size(); ++i)
	{
		Mix_FreeMusic( music_loops[i] );
		music_loops[i] = NULL;
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

		if (!loadLevels("Config/configLevels.txt") )
		{
			std::cout << "Error loading map !!" << std::endl;
		}
		else
		{
			if (!m_world.loadWorld(level_path[0]))
			{
				cout << level_path[0];
				std::cout << "s07 error loading map" << std::endl;
			}

			//Load media
			if (!loadMedia())
			{
				printf("Failed to load media!\n");
			}
			else
			{


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
				Menu menu;
				// The Game loop
				while (GAME_RUNNING)
				{
					//TODO map to level , and button music
					Sound::play_music(*this, 0);
					curr_time = SDL_GetTicks();
					time_passed = curr_time - prev_time;
					if (time_passed < 15)
					{
						continue;
					}

					prev_time = curr_time;
					ce = handler.handle();

                    //to be replaced with game over / win
					if (m_world.player -> completely_dead && !Player::lives) GAME_RUNNING = false;

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
								if (!menu.menu)
								{
                                    deletion = actor->update(time_passed, ce.ke);
                                }
								if (actor->type != PLAYER)
								{
									actor->render(gRenderer, time_passed, *this);
								}
                                if (!deletion) k++;
							}
						}
					}
					m_world.player->render(gRenderer, time_passed, *this);
					m_world.player->play_sound(*this);
					menu.update(time_passed, ce.me);
                    menu.render_menu(gRenderer);
					//Update screen
					SDL_RenderPresent(gRenderer);

					if (m_world.player->end_level == true)
					{
						m_world.destroyWorld();
						current_level++;
						if (current_level >= level_path.size())
						{
							GAME_WON = true;
							GAME_RUNNING = false;
							break;
						}
						else if (!m_world.loadWorld(level_path[current_level]))
						{
							cout << "ERROR s37: Failed to laod next level";
						}
					}

				}
			}
		}
	}

	//Free resources and close SDL
	close();

}
