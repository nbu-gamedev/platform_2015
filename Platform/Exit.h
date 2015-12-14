#pragma once
#include "Actor.h"
class Exit :
	public Actor
{
public:
	Exit(SDL_Rect rect, int i, int j);
	~Exit();
	virtual bool update(int time_passed, Key_event* ke);
	virtual void render(SDL_Renderer* renderer, int time_passed, CoreEngine &core);
	bool open = false;
};

