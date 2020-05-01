#pragma once
#pragma once
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"

class Texture2D;

class GameScreenLuigiWin : GameScreen
{
public:
	GameScreenLuigiWin(SDL_Renderer* renderer);
	~GameScreenLuigiWin();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	Texture2D* mBackgroundTexture;

	bool SetUpLevel();
};