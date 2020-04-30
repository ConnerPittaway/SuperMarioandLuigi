#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Commons.h"
#include "LevelMap.h"
#include "Texture2D.h"
#include "LevelLoader.h"
#include "Camera.h"

class POWBlock
{
public:
	POWBlock(Camera* cam, SDL_Renderer* renderer, LevelMap* map, LevelLoader* load, Vector2D position);
	~POWBlock();
	void Render(Camera* cam);
	Rect2D GetCollisionBox();
	void TakeAHit();
	bool IsAvaliable();

private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;
	LevelLoader* mLoad;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumberOfHitsLeft;
};

