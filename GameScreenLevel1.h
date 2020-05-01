#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "SDL.h"
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "LevelMap.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include <iostream>
#include "MarioScore.h"
#include "LuigiScore.h"
#include <vector>

class Texture2D;

class Character;

class PowBlock;

using namespace::std;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	CharacterMario* mCharacterMario;
	CharacterLuigi* mCharacterLuigi;
	CharacterKoopa* mKoopa;

	MarioScore* mMarioScore;
	LuigiScore* mLuigiScore;

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void UpdatePOWBlock();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	bool SetUpLevel();

	LevelMap* mLevelMap;

	void SetLevelMap();

	PowBlock* mPowBlock;

	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;

	void DoScreenshake();

	vector<CharacterKoopa*> mEnemies;

	float mKoopaTimer;
};

#endif //_GAMESCREENLEVEL1_H