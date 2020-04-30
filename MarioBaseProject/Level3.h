#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "LevelMap.h"
#include "POWBlock.h"
#include "BlockCollider3.h"
#include "LevelLoader.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include "PowerBlock.h"
#include "POWBlock.h"
#include "Coin.h"
#include "SoundEffects.h"
#include "GameScreenManager.h"
#include <vector>
#include "Globals.h"
#include "CharacterLuigi.h"

class Texture2D;
class Character;

class Level3 : GameScreen
{
public:
	Level3(SDL_Renderer* renderer);
	~Level3();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* mScoreText;
	Texture2D* mText;
	Texture2D* mLivesText;
	//Background
	Texture2D* mBackgroundTexture;

	//Characters
	CharacterKoopa* koopaCharacter;
	vector<CharacterKoopa*> mEnemies;

	//Blocks
	PowerBlock* powerBlock;
	vector<PowerBlock*> mPowerBlocks;

	//Coins
	Coin* coin;
	vector<Coin*> mCoins;

	POWBlock* mpowBlock;

	bool CheckWin();

	void UpdatePowerBlock();
	void UpdatePOWBlock();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins();

	//Create things
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreatePowerBlock(Vector2D position);
	void CreateCoins(Vector2D position);

	float mBackgroundYPos;
	bool SetUpLevel();
	void SetLevelMap();
	LevelMap* mLevelMap;
	BlockCollider3* mBetterCollisionManager;
	CharacterMario* mMarioCharacter;
	CharacterLuigi* mLuigiCharacter;
	LevelLoader* mLoader;
	char map2[MAP_WIDTH][MAP_HEIGHT];
	int map[MAP_WIDTH][MAP_HEIGHT];

	//Tiles
	Texture2D* mBrickTexture;
	Texture2D* mFloorTexture;
	Texture2D* mPoleTexture;
	Texture2D* mPowerTexture;
	Texture2D* mStairTexture;
	Texture2D* mTopTexture;
	Texture2D* mBLPipeTexture;
	Texture2D* mBRPipeTexture;
	Texture2D* mTLPipeTexture;
	Texture2D* mTRPipeTexture;

	//Camera
	Camera* mCamera;

	//Music
	SoundEffects* mSounds;

	//DeltaTime
	//Time
	Uint32 gOldTime;

	int CurrentTime = 0;
};
