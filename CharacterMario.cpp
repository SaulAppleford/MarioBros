#include "CharacterMario.h"
#include <iostream>
#include "Texture2D.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = FACING_RIGHT;

	mSingleSpriteWidth = 42;
	mSingleSpriteHeight = 32;
}

CharacterMario::~CharacterMario()
{
	delete mTexture;
	mTexture = NULL;
}

void CharacterMario::Render()
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
	if (!mTexture->LoadFromFile("Images/Mario.png"))
	{
		cout << "Failed to load da Mario!" << endl;
	}
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	//Collision position variables
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	//Deal with gravity.
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		//Collided with ground, so we can jump again
		mCanJump = true;
	}

	if (mJumping)
	{
		mPosition.y -= mJumpForce * deltaTime;

		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (mJumpForce <= 0.0f)
		{
			mJumping = false;
		}
	}

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}

	if (mPosition.x < -30.0f && mPosition.x > -150.0f)
	{
		mPosition.x = 485.0f;
	}

	if (mPosition.x > 485.0f)
	{
		mPosition.x = -25.0f;
	}
	if (mPosition.x < -150.0f)
	{
		mMovingLeft = false;
		mMovingRight = false;
		mCanJump = false;
		mJumping = true;
	}

	switch (e.type)
	{
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = false;
			break;

		case SDLK_RIGHT:
			mMovingRight = false;
			break;

		case SDLK_h:
			cout << "X Position is " << mPosition.x << endl;
			cout << "Y Position is " << mPosition.y << endl;
			cout << "Foot position is " << footPosition << endl;
			cout << mSingleSpriteWidth << endl;
			cout << mSingleSpriteHeight << endl;
			break;

		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			Character::Jump();
			break;
		case SDLK_LEFT:
			mMovingLeft = true;
			mMovingRight = false;
			break;
		case SDLK_RIGHT:
			mMovingLeft = false;
			mMovingRight = true;
			break;
		}
	}
}

void CharacterMario::CancelJump()
{
	mJumpForce = 0.0f;
	mJumping = false;
}

void CharacterMario::AddGravity(float deltaTime)
{
	mPosition.y += GRAVITY * deltaTime;
	mCanJump = false;
}

bool CharacterMario::IsJumping()
{
	if (mJumping)
	{
		return true;
	}

	return false;
}