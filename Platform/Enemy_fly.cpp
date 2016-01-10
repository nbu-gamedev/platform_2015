#include "Enemy_fly.h"
#include "CoreEngine.h"


Enemy_fly::Enemy_fly(SDL_Rect pos, std::vector<Actor*>** world, Object obj)
	: Enemy(pos, world,obj)
{
}

Enemy_fly::~Enemy_fly()
{
}


void Enemy_fly::render(SDL_Renderer * renderer, int time_passed, CoreEngine & core)
{
	last_rendered += time_passed;
	if (last_rendered > 100)
	{
		frame++;
		frame %= core.enemy_fly_textures.size();
		last_rendered -= 100;
	}

	if (direction < 0)
	{
		SDL_RenderCopy(renderer, core.enemy_fly_textures[frame], NULL, &pos_rect);

	}
	else
	{
		SDL_RenderCopyEx(renderer, core.enemy_fly_textures[frame], NULL, &pos_rect, 180.0f, NULL, SDL_FLIP_VERTICAL);
	}
}

