#include "SoundFX.h"
#include "SDL_mixer.h"
#include <string>

SoundFX* SoundFX::instance = NULL;

SoundFX::SoundFX()
{

}

SoundFX::~SoundFX()
{
	instance = NULL;
}

SoundFX* SoundFX::GetInstance()
{
	if (!instance)
	{
		instance = new SoundFX;
	}

	return instance;
}

void SoundFX::Play(string path)
{
	fx = Mix_LoadWAV(path.c_str());

	if (fx == NULL)
	{
		cout << "Failed to load sound effect! Error: " << Mix_GetError() << endl;
	}

	Mix_PlayChannel(-1, fx, 0);

}