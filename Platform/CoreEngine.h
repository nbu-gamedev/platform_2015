#pragma once
#include <iostream>
#include <string>
#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#endif

#include "Coin.h"
#include "World.h"
#include "Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Input_Handler.h"

class CoreEngine
{
public:


    const char* M_WINDOW_NAME = "Platform";

	//The window we'll be rendering to
	SDL_Window* gWindow;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//Background texture
	SDL_Texture* background_texture;

	//Player textures
	vector<SDL_Texture*> player_textures;
	SDL_Texture* player_dead_texture;
	SDL_Texture* player_jump_texture;

	//Terrain textures
	vector<SDL_Texture*> tiles_textures;

	//Enemy textures
	 vector<SDL_Texture*> enemy_textures;
	 SDL_Texture* enemy_dead_texture;
	//Coin textures
	 vector<SDL_Texture*> coin_textures;
	//Exit textures
	 vector<SDL_Texture*> exit_textures;

	 //Sound effects
	 vector<Mix_Chunk*> sound_effects;
	
	 //Map paths
	 vector<string> level_path;

	//world
	World m_world;

public:
	CoreEngine();
	void runGamingLoop();
	bool init();
	bool loadMedia();
	bool loadLevels(string levels);
	void close();
private:
	//Loads individual image
//	SDL_Surface* loadSurface(std::string path);   //outdated
	//Loads individual image as texture
	SDL_Texture* loadTexture(std::string path);
	int current_level;
};
