#include "World.h"
#include "Globals.h"
#include "Enemy.h"

bool World::loadWorld(string file)
{
	string toParse[] = {
		{"map version"},
		{"tileset firstgid"},
		{"layer name"}
	};
	constexpr int elementsToParse = sizeof(toParse) / sizeof(string);
	// Array of functions to handled the parsing of the elements in the "toParse" array
	// The i-th function is suppose to parse the i-the element in the toParse array
	void(World::*parseFunc[elementsToParse])(const string &line, ifstream &file) = {};
	parseFunc[0] = &World::parseDimensions;
	parseFunc[1] = &World::parseObject;
	parseFunc[2] = &World::parseGrid;

	// Looping the lines in the file and calling parse
	string line;
	ifstream myfile(file);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int i = 0; i < elementsToParse; i++)
			{
				size_t found = line.find(toParse[i]);
				if (string::npos != found)
				{
					(*this.*parseFunc[i])(line, myfile);
				}
			}

		}
		myfile.close();
	}
	else
	{
		cout << "ERROR s01: Cant open file" << endl;
		return false;
	}


	// Set world size
	pixelsPerTile = mapInfo.tileWidth;
	screenWidth = mapInfo.yTiles * pixelsPerTile;
	screenHeight = mapInfo.xTiles * pixelsPerTile;
	/* REMINDER: This is getting initialized in parseGrid()
	grid_width = screenWidth / pixelsPerTile;
	grid_height = screenHeight / pixelsPerTile;
	*/

	return true;
}

World::World()
{

}

World::~World()
{
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//   TODO: free the world grid
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
// parse and set the xTiles, yTiles, tileWidth, tileHeight of the mapInfo struct;
void World::parseDimensions(const string &line, ifstream &file)
{
	string toParse[] = { { "width=\"" },{ "height=\"" },{ "tilewidth=\"" },{ "tileheight=\"" } };

	mapInfo.yTiles = getValueAfter(toParse[0], line);
	mapInfo.xTiles = getValueAfter(toParse[1], line);
	mapInfo.tileWidth = getValueAfter(toParse[2], line);
	mapInfo.tileHeight = getValueAfter(toParse[3], line);

}
void World::parseObject(const string & line, ifstream &file)
{
	string toParse[] = { { "tilewidth=\"" },{ "tileheight=\"" },{ "tilecount=\"" },{ "firstgid=\"" } };
	ObjectInfo info;
	info.width = getValueAfter(toParse[0], line);
	info.height = getValueAfter(toParse[1], line);
	info.tilecount = getValueAfter(toParse[2], line);
	info.number = getValueAfter(toParse[3], line) - 1;
	// get the next line and read the filePath of the image
	string nextLine;
	getline(file, nextLine);
	size_t start_location = nextLine.find("\"");
	int offset = 1;
	while (nextLine[start_location + offset] != '"')
	{
		info.filePath += nextLine[start_location + offset];
		offset++;
	}
	loadedObjects.push_back(info);

}
void World::parseGrid(const string & line, ifstream &file)
{
	grid_width = getValueAfter("width=\"", line);
	grid_height = getValueAfter("height=\"", line);
	string row;
	getline(file, row);
	// init the array
	worldGrid = new Actor**[grid_height];
	for (int i = 0; i < grid_height; i++)
	{
		worldGrid[i] = new Actor*[grid_width];
	}
	// clear if any left coins (from another level or sth)
	if (Coin::coins_to_collect)
	{
        Coin::coins_to_collect = 0;
	}
	int current;
	char comma;
	for (int i = 0; i < grid_height; i++)
	{
		getline(file, row);
		stringstream rowDataStream(row);
		for (int j = 0; j < grid_width; j++)
		{
			rowDataStream >> current >> comma;

			SDL_Rect rect;
			if (current != 0)
			{
				rect.w = loadedObjects[current-1].width;
				rect.h = loadedObjects[current-1].height;
				rect.y = (i + 1) * mapInfo.tileHeight - loadedObjects[current-1].height;
				rect.x = j*mapInfo.tileWidth + mapInfo.tileWidth / 2. - loadedObjects[current-1].width / 2.;
				rect.h *= SCALE_FACTOR;
				rect.w *= SCALE_FACTOR;
				rect.x *= SCALE_FACTOR;
				rect.y *= SCALE_FACTOR;

			}

			switch (current)
			{
			case 0:
				worldGrid[i][j] = NULL;
				break;
			case 1:
				worldGrid[i][j] = new terrain(rect, i, j, GROUND);
				worldGrid[i][j]->loadedNumber = current - 1;
				break;
			case 2:
				worldGrid[i][j] = new terrain(rect, i, j, GROUND_DIRT);
				worldGrid[i][j]->loadedNumber = current - 1;
				break;
			case 3:
                player = new Player(rect, worldGrid);
				worldGrid[i][j] = player;
				worldGrid[i][j]->loadedNumber = current - 1;
				player_i = i;
				player_j = j;
				player_pos = rect;
				break;
			case 4:
				worldGrid[i][j] = new Enemy(rect, worldGrid, SLIME);
				worldGrid[i][j]->loadedNumber = current - 1;
				break;
			case 5:
				worldGrid[i][j] = new Coin(rect);
				worldGrid[i][j]->loadedNumber = current - 1;
				Coin::coins_to_collect++;
				break;
			default:
				worldGrid[i][j] = NULL;
				break;
			}
		}
	}

}

// Get the int value between the toParse string and the next quotation mark
int World::getValueAfter(const string &toParse, const string &line)
{
	size_t start_location;
	size_t offset = toParse.size();
	int result = 0;

	offset = toParse.size();
	start_location = line.find(toParse);
	// Convert the sequence of characters representing the integer value to integer
	while (line[start_location + offset] != '"')
	{
		result *= 10;
		result += (line[start_location + offset]) - '0';
		offset++;
	}

	return result;
}

void World::respawn()
{
    //find player
    for (int i = 0; i < grid_height; i++)
	{
        for (int j = 0; j < grid_width; j++)
		{
            if (worldGrid[i][j] && dynamic_cast<Player*>(worldGrid[i][j]))
            {
                //delete old player
                delete player;
                player = new Player(player_pos, worldGrid);
                worldGrid[player_i][player_j] = player;
                return;
            }
		}
    }
}























































