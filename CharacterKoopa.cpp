#include "CharacterKoopa.h"
#include "Texture2D.h"
#include "Constants.h"
#include "SoundFX.h"

using namespace::std;

class Character;

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, FACING startFacing, float movementSpeed, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{	
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;
	
	mInjured = false;
	mAlive = true;	
	mInjuredTime = INJURED_TIME;
	
	mSingleSpriteWidth = mTexture->GetWidth()/2;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{
	delete mTexture;
	mTexture = NULL;
}

void CharacterKoopa::TakeDamage()
{
	if (!mInjured)
	{
		SoundFX::GetInstance()->Play("Sounds/koopahurt.wav");
		mInjured = true;
		mInjuredTime = INJURED_TIME;
		Jump();
	}
	else
	{
		SetAlive(false);
		SoundFX::GetInstance()->Play("Sounds/koopadead.wav");
	}
}

void CharacterKoopa::Jump()
{
	mJumpForce = JUMP_FORCE_SMALL;

	mJumping = true;
	mCanJump = false;
}

void CharacterKoopa::FlipRightWayUp()
{
	!mFacingDirection;
	mInjured = false;
	Jump();
}

void CharacterKoopa::Render()
{
	int left = 0.0f;

	mSingleSpriteWidth = 32;
	mSingleSpriteHeight = 30;

	if (mInjured)
	{
		left = mSingleSpriteWidth;
	}

	SDL_Rect srcRect = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(srcRect, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(srcRect, destRect, SDL_FLIP_HORIZONTAL);
	}
	if (!mTexture->LoadFromFile("Images/Koopa.png"))
	{
		cout << "Failed to load da Koopas!" << endl;
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	
	//Collision position variables
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	//Deal with gravity.
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
	{
		AddGravity(deltaTime);
		mMovingLeft = false;
		mMovingRight = false;
	}

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}
	if (mPosition.x < -30.0f)
	{
		mFacingDirection = FACING_RIGHT;
	}

	if (mPosition.x > 475.0f)
	{
		mFacingDirection = FACING_LEFT;
	}
	if (!mInjured)
	{
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingRight = true;
			mMovingLeft = false;
		}
	}
	else
	{
		mMovingLeft = false;
		mMovingRight = false;

		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0)
		{
			FlipRightWayUp();
		}
	}
}

Rect2D CharacterKoopa::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight);
}

void CharacterKoopa::SetAlive(bool alive)
{
	mAlive = alive;
}

bool CharacterKoopa::GetAlive()
{
	return mAlive;
}