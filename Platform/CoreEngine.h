#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <SDL_image.h>

class CoreEngine 
{
private:
	
	const int M_WINDOW_HEIGHT = 720;
	const int M_WINDOW_WIDTH = 1280;
	const char *M_WINDOW_NAME = "Platform";


	

	//The window we'll be rendering to
	SDL_Window* gWindow;

	//The surface contained by the window
	SDL_Surface* gScreenSurface;

	//Current displayed PNG image
	SDL_Surface* gPNGSurface;

public:
	CoreEngine();
	void runGamingLoop();
	bool init();
	bool loadMedia();
	void close();
private:
	//Loads individual image
	SDL_Surface* loadSurface(std::string path);
};