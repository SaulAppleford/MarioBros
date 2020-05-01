#pragma once
#ifndef _SOUNDFX_H
#define	_SOUNDFX_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>

using namespace::std;

class SoundFX
{
public:
	SoundFX();
	~SoundFX();

	static SoundFX* GetInstance();

	void Play(string path);

	static SoundFX* instance;

private:

	Mix_Chunk* fx;
};

#endif