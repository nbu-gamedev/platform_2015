#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "Actor.h"
#include "Player.h"
#include "Terrain.h"

using namespace std;

// This class need to be initialised with the loadWorld function witch will return true or false on success or failure respectively.
class World
{
private:


public:


	// the grid with all the interactable objects
	vector<Actor*> **worldGrid;
	//Actor*** worldGrid;
	Player* player;
	// Load the world from tmx file
	bool loadWorld(string file);

	//player's info(needed for respawn)
	int player_i;
	int player_j;
    SDL_Rect player_pos;

	// Construcor and destructor l
	World();
	~World();
// this should be private
public:

	// function to parse the XML file
	void parseDimensions(const string &line, ifstream &file);
	void parseObject(const string &line, ifstream &file);
	void parseGrid(const string &line, ifstream &file);
	int getValueAfter(const string &toParse, const string &line);
	void destroyWorld()
	{
		for (int i = 0; i < GRID_HEIGHT; i++)
		{
			for (int j = 0; j < GRID_WIDTH; j++)
			{
				for (Actor* actor : worldGrid[i][j])
				{
					delete actor;
				}
				worldGrid[i][j].clear();
			}
		}
		loadedObjects.clear();
	}

	void respawn();

	// Size of the world
	int world_width_in_pixels;
	int world_height_in_pixels;
	int pixelsPerTile;
	// The number of vertical and horizontal tiles and the width and height of each tile
	struct TiledMap
	{
		int xTiles;
		int yTiles;
		int tileWidth;
		int tileHeight;

	} mapInfo = {};
	// The objects that are getting loaded
	struct ObjectInfo
	{
		string name;
		// size of the image
		int width;
		int height;
		// size in tiles
		int tilecount;
		// the number of the object
		int number;
		// the path to the image file
		string filePath;
	};
	// holds the information for the loaded object, see ObjectInfo struct for more info
	vector<ObjectInfo> loadedObjects;
};

