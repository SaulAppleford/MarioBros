#pragma once
#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include "SDL.h"
#include "Commons.h"
#include <string>

class GameScreen;

class GameScreenManager
{
private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;

public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);

	bool mMenu;
};

#endif //_GAMESCREENMANAGER_H