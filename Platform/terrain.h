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
	void render();
};