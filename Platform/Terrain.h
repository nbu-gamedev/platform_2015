#pragma once
#include "Actor.h"

class Terrain :
	public Actor
{
public:
	Terrain();
	Terrain(SDL_Rect rect, int i, int j, Object obj);
	~Terrain();
	Object type;

	bool update(int time_passed, Key_event* ke);
	void render(SDL_Renderer* renderer, int time_passed, CoreEngine &core);
};
