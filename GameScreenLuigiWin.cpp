#include "GameScreenLuigiWin.h"
#include <iostream>
#include "Texture2D.h"
#include "GameScreenManager.h"
#include "SoundFX.h"

GameScreenLuigiWin::GameScreenLuigiWin(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLuigiWin::~GameScreenLuigiWin()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenLuigiWin::Update(float deltaTime, SDL_Event e)
{

}

void GameScreenLuigiWin::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

bool GameScreenLuigiWin::SetUpLevel()
{
	
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/LuigiWin.png"))
	{
		cout << "No Luigi BG!" << endl;
		return false;
	}
	else
	{
		return true;
	}

	SoundFX::GetInstance()->Play("Sounds/luigiwin.wav");
}