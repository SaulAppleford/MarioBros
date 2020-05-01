#include "SDL.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenManager.h"
#include "GameScreenMenu.h"
#include "GameScreenLuigiWin.h"

using namespace::std;

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;
	mMenu = true;

	//Ensure the first screen is set up
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);

	if(mMenu == true)
	if (e.type == SDL_KEYDOWN)
	{
		ChangeScreen(SCREEN_LEVEL1);
		mMenu = false;
	}
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear old screen.
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenLevel1* tempScreen;
	GameScreenMenu* menScreen;
	GameScreenLuigiWin* luiScreen;

	switch (newScreen)
	{
	case SCREEN_INTRO:
		break;
	case SCREEN_MENU:
		menScreen = new GameScreenMenu(mRenderer);
		mCurrentScreen = (GameScreen*)menScreen;
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	case SCREEN_LWIN:
		luiScreen = new GameScreenLuigiWin(mRenderer);
		mCurrentScreen = (GameScreen*)luiScreen;
		break;
	case SCREEN_GAMEOVER:
		break;
	case SCREEN_MWIN:
		break;
	default:
		break;
	}
}