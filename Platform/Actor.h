#pragma once


class Actor
{

public:
	virtual void update();
	virtual void render();

	SDL_Rect pos_rect;
	SDL_Rect img_rect;
	int speed; //
};
