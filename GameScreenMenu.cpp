#include "GameScreenMenu.h"
#include <iostream>
#include "Texture2D.h"
#include "GameScreenManager.h"

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenMenu::~GameScreenMenu()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{
	
}

void GameScreenMenu::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

bool GameScreenMenu::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Menu.png"))
	{
		cout << "No Menu BG!" << endl;
		return false;
	}
	else
	{
		return true;
	}
}