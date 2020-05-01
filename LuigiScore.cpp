#include "LuigiScore.h"
#include "GameScreenManager.h"
#include <string>

using namespace::std;

LuigiScore::LuigiScore(SDL_Renderer* renderer)
{
	string imagePath = "Images/LuigiScore.png";
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load texture: " << imagePath << endl;
		return;
	}

	int mScore = 1;
	mPosition = Vector2D(394, 0);
}

LuigiScore::~LuigiScore()
{
	mRenderer = NULL;

	delete mTexture;
	mTexture = NULL;
}

void LuigiScore::ScoreUp()
{
	mScore++;

	if (mScore >= 10)
	{
		cout << "Luigi wins" << endl;
	}
}

void LuigiScore::Render()
{
	//Get portion of spritesheet to draw.
	int left = 96 * (mScore);

	SDL_Rect srcRect = { left, 0, 96, 32 };

	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), 96, 32 };

	mTexture->Render(srcRect, destRect, SDL_FLIP_NONE);
}