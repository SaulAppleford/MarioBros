#include "Character.h"
#include "Texture2D.h"
#include "Commons.h"
#include "Constants.h"
#include "Collisions.h"
#include "PowBlock.h"
#include "SoundFX.h"
#include <string>

using namespace::std;

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);

	mPosition.x = startPosition.x;
	mPosition.y = startPosition.y;

	mCanJump = true;
	mJumpForce = 0.0f;
	mJumping = false;

	

	mMovingLeft = false;
	mMovingRight = false;

	mCollisionRadius = 15.0f;

	mCurrentLevelMap = map;

	mSingleSpriteWidth = mTexture->GetWidth();
	mSingleSpriteHeight = mTexture->GetHeight();
}

Character::~Character()
{
	delete mRenderer;
	mRenderer = NULL;
}

void Character::MoveLeft(float deltaTime)
{
	mFacingDirection = FACING_LEFT;
	mPosition.x -= MOVESPEED * deltaTime;
}

void Character::MoveRight(float deltaTime)
{
	mFacingDirection = FACING_RIGHT;
	mPosition.x += MOVESPEED * deltaTime;
}

void Character::AddGravity(float deltaTime)
{
	mPosition.y += GRAVITY * deltaTime;
	mCanJump = false;
}

void Character::Jump()
{
	
	if (!mJumping)
	{
		mJumpForce = INITAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
		SoundFX::GetInstance()->Play("Sounds/jump.wav");
	}
}

bool Character::IsJumping()
{
	if (mJumping)
	{
		return true;
	}

	return false;
}

void Character::CancelJump()
{
	mJumpForce = 0.0f;
	mJumping = false;
}

void Character::Render()
{
	
}

void Character::Update(float deltaTime, SDL_Event e)
{
	
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition.x = newPosition.x;
	mPosition.y = newPosition.y;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}