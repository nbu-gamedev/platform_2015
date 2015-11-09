#pragma once
#include "Actor.h"
class terrain :
	public Actor
{
public:
	terrain();
	terrain(int loadedNumber);
	~terrain();

	void update();
	void render();
};

