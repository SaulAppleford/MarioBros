#pragma once
#ifndef _MARIOSCORE_H
#define _MARIOSCORE_H

#include "SDL.h"
#include "Commons.h"
#include "Texture2D.h"
#include <iostream>
#include <string>

using namespace::std;

class Texture2D;

class MarioScore
{
public:
	MarioScore(SDL_Renderer* renderer);
	~MarioScore();

	void Render();
	void ScoreUp();

private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	int mScore;
};

#endif