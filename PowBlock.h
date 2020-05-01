#pragma once
#ifndef _POWBLOCK_H
#define _POWBLOCK_H

#include "SDL.h"
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include <iostream>
#include <string>

using namespace::std;

class Texture2D;

class LevelMap;

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();

	void Render();
	
	void TakeAHit();
	inline
		bool IsAvailable()
	{
		return mNumberOfHitsLeft > 0;
	};

	Rect2D GetCollisionBox()
	{
		return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight) ;
	};

private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumberOfHitsLeft;
};

#endif