#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "Actor.h"
#include "terrain.h"

using namespace std;

// This class need to be initialised with the loadWorld function witch will return true or false on success or failure respectively.
class World
{
private:


public:


	// the grid with all the interactable objects
	Actor*** worldGrid;

	// Load the world from tmx file
	bool loadWorld(string file);


	// Construcor and destructor
	World();
	~World();
// this should be private
public:

	// function to parse the XML file
	void parseDimensions(const string &line, ifstream &file);
	void parseObject(const string &line, ifstream &file);
	void parseGrid(const string &line, ifstream &file);
	int getValueAfter(const string &toParse, const string &line);
	// Size of the world
	int screenWidth;
	int screenHeight;
	int pixelsPerTile;
	int grid_width;
	int grid_height;
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

