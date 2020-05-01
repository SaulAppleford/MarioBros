#include "CharacterLuigi.h"
#include <iostream>
#include "Texture2D.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = FACING_LEFT;
	
	mSingleSpriteWidth = 42;
	mSingleSpriteHeight = 32;
}

CharacterLuigi::~CharacterLuigi()
{
	delete mTexture;
	mTexture = NULL;
}

void CharacterLuigi::Render()
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
	if (!mTexture->LoadFromFile("Images/Luigi.png"))
	{
		cout << "Failed to load da Luigi!" << endl;
	}
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
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
		case SDLK_a:
			mMovingLeft = false;
			break;

		case SDLK_d:
			mMovingRight = false;
			break;

		case SDLK_h:
			cout << "X Position is " << mPosition.x << endl;
			cout << "Y Position is " << mPosition.y << endl;
			cout << "Foot position is " << footPosition << endl;
			break;

		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			Character::Jump();
			break;
		case SDLK_a:
			mMovingLeft = true;
			mMovingRight = false;
			break;
		case SDLK_d:
			mMovingLeft = false;
			mMovingRight = true;
			break;
		}
	}
}

void CharacterLuigi::CancelJump()
{
	mJumpForce = 0.0f;
	mJumping = false;
}

void CharacterLuigi::AddGravity(float deltaTime)
{
	mPosition.y += GRAVITY * deltaTime;
	mCanJump = false;
}

bool CharacterLuigi::IsJumping()
{
	if (mJumping)
	{
		return true;
	}

	return false;
}