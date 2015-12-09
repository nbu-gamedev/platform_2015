#pragma once
#include "Actor.h"

class terrain :
	public Actor
{
public:
	terrain();
	terrain(SDL_Rect rect, int i, int j, Object obj);
	~terrain();
	Object type;

	bool update(int time_passed, Key_event* ke);
	void render(SDL_Renderer* renderer, int time_passed, CoreEngine &core);
};
