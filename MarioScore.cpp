#include "MarioScore.h"
#include "GameScreenManager.h"
#include <string>

using namespace::std;

class GameScreenManager;

MarioScore::MarioScore(SDL_Renderer* renderer)
{
	string imagePath = "Images/MarioScore.png";
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load texture: " << imagePath << endl;
		return;
	}

	int mScore = 1;
	mPosition = Vector2D(32, 0);
}

MarioScore::~MarioScore()
{
	mRenderer = NULL;

	delete mTexture;
	mTexture = NULL;
}

void MarioScore::ScoreUp()
{
	mScore++;

	if (mScore >= 10)
	{
		GameScreenManager(mRenderer, SCREEN_MWIN);
	}
}

void MarioScore::Render()
{
		//Get portion of spritesheet to draw.
		int left = 96 * (mScore);

		SDL_Rect srcRect = { left, 0, 96, 32 };

		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), 96, 32 };

		mTexture->Render(srcRect, destRect, SDL_FLIP_NONE);
}