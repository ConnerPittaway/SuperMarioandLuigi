#pragma once
#include "Character.h"
#include "Texture2D.h"
#include "LevelLoader.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, LevelLoader* load);
	~CharacterLuigi();

	virtual void Render(Camera* cam, float deltaTime);
	virtual void Update(float deltaTime, SDL_Event e);
	Rect2D GetLuigiCollisionBox();
	void SmallJump();

private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	LevelMap* mCurrentLevelMap;
	LevelLoader* mLoad;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	//Animation
	float mFrameDelay;
	int mCurrentFrame;
};