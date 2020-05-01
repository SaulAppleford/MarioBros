#pragma once
#include <SDL.h>
#include "Commons.h"
#include "Character.h"
#include "Texture2D.h"
#include "Collisions.h"

using namespace::std;

class Texture2D;

class CharacterKoopa : Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, FACING startFacing, float movementSpeed, LevelMap* map);
	~CharacterKoopa();

	void TakeDamage();
	void Jump();
	inline
	Vector2D GetPosition()
	{
		return mPosition;
	}

	Rect2D GetCollisionBox();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	bool GetAlive();
	void SetAlive(bool alive);

	inline
		bool GetInjured()
		{
			return mInjured;
		}

private:
	void FlipRightWayUp();

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	bool mInjured;
	float mInjuredTime;
	float mMovementSpeed;
	
	bool mAlive;
};