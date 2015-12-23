#pragma once


class CoreEngine;
enum SoundEvents;
class Sound
{
public:
	static void play_sound(CoreEngine &core, SoundEvents sound);
	static void play_music(CoreEngine &core, int loop_number, bool music_enabled);
	
};