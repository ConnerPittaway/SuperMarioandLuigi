#pragma once
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

class Texture2D;

class Intro : GameScreen
{
public:
	Intro(SDL_Renderer* renderer);
	~Intro();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* mText;
	//Background
	Texture2D* mBackgroundTexture;

	float mBackgroundYPos;
	bool SetUpLevel();
	void SetLevelMap();
	LevelMap* mLevelMap;
	LevelLoader* mLoader;

	//Camera
	Camera* mCamera;

	//Music
	SoundEffects* mSounds;

	//DeltaTime
	//Time
	Uint32 gOldTime;

	int CurrentTime = 0;
};

