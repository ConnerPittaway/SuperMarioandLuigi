#pragma once
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "LevelMap.h"
#include "POWBlock.h"
#include "BlockCollider.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include <vector>

class Texture2D;
class Character;
class POWBlock;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	Character* myCharacter;
	Character* myCharacter2;
	CharacterMario* mMarioCharacter;
	CharacterKoopa* koopaCharacter;
	BlockCollider* CollisionManager;

	bool SetUpLevel();
	void SetLevelMap();
	LevelMap* mLevelMap;
	POWBlock* mPowBlock;
	
	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;
	void DoScreenshake();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdatePOWBlock();
	void CheckCollision();

	vector<CharacterKoopa*> mEnemies;
};
