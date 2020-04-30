#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Commons.h"
#include "LevelLoader.h"
#include "Texture2D.h"
#include "Camera.h"

class PowerBlock
{
public:
	PowerBlock(Camera* cam, SDL_Renderer* renderer, LevelLoader* load, Vector2D startPosition);
	~PowerBlock();
	void Render(Camera* cam, float deltaTime);
	Rect2D GetCollisionBox();
	void TakeAHit();
	bool IsAvaliable();

private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelLoader* mLoad;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	Camera* camera;
	int mNumberOfHitsLeft;

	//Animation
	float mFrameDelay;
	int mCurrentFrame;
};
