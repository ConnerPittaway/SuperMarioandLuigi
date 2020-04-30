#pragma once
#include "Character.h"
#include "Texture2D.h"
#include "LevelLoader.h"
#include "Camera.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(Camera* cam, SDL_Renderer* renderer, std::string imagePath, LevelMap* map, LevelLoader* load, Vector2D startPosition, FACING startFacing, float movementSpeed);
	~CharacterKoopa();
	void TakeDamage();
	void Jump();
	virtual void Render(Camera* cam, float deltaTime);
	virtual void Update(float deltaTime, SDL_Event e);
	Rect2D GetKoopaCollisionBox();

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mInjuredTime = 1.0f;
	void FlipRightwayUp();


	LevelMap* mCurrentLevelMap;
	LevelLoader* mLoad;
	Camera* camera;

	//Animation
	float mFrameDelay;
	int mCurrentFrame;
};

