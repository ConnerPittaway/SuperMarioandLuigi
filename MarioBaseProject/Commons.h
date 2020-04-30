#pragma once
#include "SDL.h"

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float h, float v)
	{
		x = h;
		y = v;
	}
};

struct Rect2D
{
	int width;
	int height;
	float x;
	float y;

	Rect2D(float a, float d, int w, int h)
	{
		x = a;
		y = d;
		width = w;
		height = h;
	}

};

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_LEVEL3,
	SCREEN_LEVEL4,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};


