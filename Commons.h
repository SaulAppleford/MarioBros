#pragma once
#ifndef _COMMONS_H
#define _COMMONS_H

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initalX, float initalY)
	{
		x = initalX;
		y = initalY;
	}
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D()
	{
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
	}

	Rect2D(float initialX, float initialY)
	{
		x = initialX;
		y = initialY;
	}

	Rect2D(float initialX, float initialY, float initialW, float initialH)
	{
		x = initialX;
		y = initialY;
		width = initialW;
		height = initialH;
	}
};


enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LWIN,
	SCREEN_GAMEOVER,
	SCREEN_MWIN
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};

#endif //_COMMONS_H