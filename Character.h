#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "SDL.h"
#include "Commons.h"
#include "LevelMap.h"
#include <iostream>
#include <string>

using namespace::std;

class Texture2D;

class LevelMap;

class Character
{
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	bool mJumping;
	bool mCanJump;
	float mJumpForce;

	float mCollisionRadius;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	FACING mFacingDirection;

	bool mMovingLeft;
	bool mMovingRight;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	LevelMap* mCurrentLevelMap;

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	inline
	float GetCollisionRadius()
	{
		return mCollisionRadius;
	}
	inline
		Rect2D GetCollisionBox()
	{
		return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight);
	};

	void AddGravity(float deltaTime);
	void Jump();
	bool IsJumping();
	void CancelJump();
	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

private:

};

#endif //_CHARACTER_H