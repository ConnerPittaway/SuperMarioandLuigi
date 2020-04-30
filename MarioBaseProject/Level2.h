#pragma once
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "LevelMap.h"
#include "POWBlock.h"
#include "BlockCollider.h"
#include "BlockCollider2.h"
#include "LevelLoader.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include <vector>

class Texture2D;
class Character;

class Level2 : GameScreen
{
public:
	Level2(SDL_Renderer* renderer);
	~Level2();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* mBackgroundTexture;
	Texture2D* mBrickTexture;

	float mBackgroundYPos;
	bool SetUpLevel();
	void SetLevelMap();
	LevelMap* mLevelMap;
	BlockCollider* mCollisionManager;
	BlockCollider2* mBetterCollisionManager;
	CharacterMario* mMarioCharacter;
	LevelLoader* mLoader;
	char map2[MAP_WIDTH][MAP_HEIGHT];
	int map[MAP_WIDTH][MAP_HEIGHT];
};

