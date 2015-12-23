#pragma once


class CoreEngine;
class Sound
{
public:
	static void play_sound(CoreEngine &core, int sound);
	static void play_music(CoreEngine &core, int loop_number, bool music_enabled);
	
};