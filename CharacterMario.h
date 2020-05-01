#pragma once
#include <SDL.h>
#include "Commons.h"
#include "Character.h"
#include "Texture2D.h"
#include "Collisions.h"

class Texture2D;

class CharacterMario : Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	float GetCollisionRadius();
	inline
		Rect2D GetCollisionBox()
	{
		return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight);
	};
	inline
		Vector2D SetPosition(Vector2D newPosition)
	{
		mPosition.x = newPosition.x;
		mPosition.y = newPosition.y;

		return Vector2D(newPosition);
	}
	inline
		Vector2D GetPosition()
	{
		return mPosition;
	}

	void Jump();
	void AddGravity(float deltaTime);
	bool IsJumping();
	void CancelJump();

};