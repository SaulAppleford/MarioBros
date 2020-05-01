#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Powblock.h"
#include "Collisions.h"
#include "SoundFX.h"
#include <iostream>

using namespace::std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	mLevelMap = NULL;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//Clear old map.
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//Set new map.
	mLevelMap = new LevelMap(map);
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mCharacterMario;
	mCharacterMario = NULL;

	delete mCharacterLuigi;
	mCharacterLuigi = NULL;

	mEnemies.clear();

	delete mPowBlock;
	mPowBlock = NULL;

	delete mMarioScore;
	mMarioScore = NULL;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (mScreenshake)
	{
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		if (mScreenshakeTime <= 0.0f)
		{
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	if (mKoopaTimer > 0.0f)
	{
		mKoopaTimer -= deltaTime;
		//cout << mKoopaTimer << endl;
	}
	if (mKoopaTimer <= 0.0f)
	{
		mKoopaTimer = 5.0f;
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
		SoundFX::GetInstance()->Play("Sounds/koopaspawn.wav");

		if (!mPowBlock->IsAvailable())
		{
			delete mPowBlock;
			mPowBlock = new PowBlock(mRenderer, mLevelMap);
			SoundFX::GetInstance()->Play("Sounds/powspawn.wav");
		}
	}

	//Update the player
	mCharacterMario->Update(deltaTime, e);
	mCharacterLuigi->Update(deltaTime, e);

	if (Collisions::Instance()->Box(mCharacterMario->GetCollisionBox(), mCharacterLuigi->GetCollisionBox()))
	{
		cout << "Characters collided!" << endl;
	}


	//Update the POW BLock
	UpdatePOWBlock();

	//Update enemies
	UpdateEnemies(deltaTime, e);
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(mCharacterMario->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			//Collided whilst jumping.
			if (mCharacterMario->IsJumping())
			{
				DoScreenshake();
				SoundFX::GetInstance()->Play("Sounds/pow.wav");
				mPowBlock->TakeAHit();
				mCharacterMario->CancelJump();
			}
		}
	}

	if (Collisions::Instance()->Box(mCharacterLuigi->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			//Collided whilst jumping.
			if (mCharacterLuigi->IsJumping())
			{
				DoScreenshake();
				SoundFX::GetInstance()->Play("Sounds/pow.wav");
				mPowBlock->TakeAHit();
				mCharacterLuigi->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			if (mEnemies[i]->GetPosition().y > 300.0f)
			{
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
				{
					mEnemies[i]->SetAlive(false);
					SoundFX::GetInstance()->Play("Sounds/koopaescape.wav");
				}
			}

			//Call Koopa update
			mEnemies[i]->Update(deltaTime, e);

			//Check collision with player
			if((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f) )
			{
				//Ignore collisions behind pipes
			}
			else
			{
				if(Collisions::Instance()->Box(mCharacterMario->GetCollisionBox(), mEnemies[i]->GetCollisionBox()))
				{
					if (mEnemies[i]->GetInjured())
					{
						mMarioScore->ScoreUp();
						mEnemies[i]->TakeDamage();
					}
					else
					{
						mCharacterMario->SetPosition(Vector2D(-200.0f, -200.0f));
						SoundFX::GetInstance()->Play("Sounds/mariohurt.wav");
					}
				}
				if (Collisions::Instance()->Box(mCharacterLuigi->GetCollisionBox(), mEnemies[i]->GetCollisionBox()))
				{
					if (mEnemies[i]->GetInjured())
					{
						mLuigiScore->ScoreUp();
						mEnemies[i]->TakeDamage();
					}
					else
					{
						mCharacterLuigi->SetPosition(Vector2D(-200.0f, -200.0f));
						SoundFX::GetInstance()->Play("Sounds/luigihurt.wav");
					}	
				}
			}

			if (!mEnemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}

		}

		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::Render()
{
	//Draw enemies.
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			mEnemies[i]->Render();
		}

	//mKoopa->Render();

	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	//Draw da character(s)
	mCharacterMario->Render();
	mCharacterLuigi->Render();

	//Draw da Pow Block
	mPowBlock->Render();

	//Drawin scores
	mMarioScore->Render();
	mLuigiScore->Render();
}

bool GameScreenLevel1::SetUpLevel()
{
	//Create level map.
	SetLevelMap();

	//Set up POW block.
	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	
	mScreenshake = false;
	mBackgroundYPos = 0.0f;
	
	//Set up the player character
	mCharacterMario = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);

	//Set up Luigi
	mCharacterLuigi = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(414, 330), mLevelMap);

	mMarioScore = new MarioScore(mRenderer);
	mLuigiScore = new LuigiScore(mRenderer);

	mKoopaTimer = 5.0f;

	//Set up bad guys
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	
	//Load the background texture.
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load background texture!" << endl;
		return false;
	}
}

void GameScreenLevel1::DoScreenshake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	SetLevelMap();
	mKoopa = new CharacterKoopa(mRenderer, "Images/Koopa.png", Vector2D(position), direction, KOOPA_SPEED, mLevelMap);
	mEnemies.push_back(mKoopa);
}
