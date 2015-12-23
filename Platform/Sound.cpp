#include "Sound.h"
#include <SDL_mixer.h>
#include "CoreEngine.h"

void Sound::play_sound(CoreEngine &core, int sound)
{
	Mix_PlayChannel(-1, core.sound_effects[sound], 0);
}

void Sound::play_music(CoreEngine & core, int loop_number, bool music_enabled)
{
	if (music_enabled)
	{
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music 
			Mix_PlayMusic(core.music_loops[loop_number], -1);
		}
			//If the music is paused 
		else if (Mix_PausedMusic() == 1)
		{
			//Resume the music 
			Mix_ResumeMusic();
		}
		
	}
	//If the music is playing 
	else
	{
		//Pause the music 
		Mix_PauseMusic();
	}
	
	//If music is being played 
	
}
