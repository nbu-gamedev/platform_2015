#pragma once
#include "Actor.h"

class terrain :
	public Actor
{
public:
	terrain();
	terrain(SDL_Rect rect, Object obj);
	~terrain();
	Object type;

	void update();
	virtual void update(Actor*** grid, int time_passed, Key_event* ke) {};
	void render(SDL_Renderer* renderer, int time_passed, CoreEngine &core);
};
