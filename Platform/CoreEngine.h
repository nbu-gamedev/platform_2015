#pragma once
#include <iostream>
#include <string>
#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#include "Coin.h"
#include "World.h"
#include "Actor.h"
#include "Player.h"
#include "Enemy.h"

class CoreEngine
{
private:

	const int M_WINDOW_HEIGHT = 720;
	const int M_WINDOW_WIDTH = 1280;
	const char *M_WINDOW_NAME = "Platform";




	//The window we'll be rendering to
	SDL_Window* gWindow;

	//The surface contained by the window
//	SDL_Surface* gScreenSurface;

	//Current displayed PNG image
//	SDL_Surface* gPNGSurface;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//Current displayed texture
	SDL_Texture* gTexture = NULL;

public:
	CoreEngine();
	void runGamingLoop();
	bool init();
	bool loadMedia();
	void close();
private:
	//Loads individual image
//	SDL_Surface* loadSurface(std::string path);   //outdated
	//Loads individual image as texture
	SDL_Texture* loadTexture(std::string path);
};
