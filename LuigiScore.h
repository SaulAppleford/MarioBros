#pragma once
#ifndef _LuigiSCORE_H
#define _LuigiSCORE_H

#include "SDL.h"
#include "Commons.h"
#include "Texture2D.h"
#include <iostream>
#include "GameScreen.h"
#include <string>

using namespace::std;

class Texture2D;

class GameScreen;

class GameScreenManager;

class LuigiScore
{
public:
	LuigiScore(SDL_Renderer* renderer);
	~LuigiScore();

	void Render();
	void ScoreUp();

private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	int mScore;
};

#endif#pragma once
