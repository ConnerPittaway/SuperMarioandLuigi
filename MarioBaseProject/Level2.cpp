#include "Level2.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include <fstream>
#include <string>

Level2::Level2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	
	mLevelMap = NULL;
}

Level2::~Level2()
{
	delete mBackgroundTexture;
	delete mBrickTexture;
	delete mLevelMap;
	delete mMarioCharacter;
	delete mCollisionManager;
	mBackgroundTexture = nullptr;
}

void Level2::Update(float deltaTime, SDL_Event e)
{

	mMarioCharacter->Update(deltaTime, e);
	mBetterCollisionManager->CheckCollision(mMarioCharacter, mMarioCharacter->GetMovingRight(), mMarioCharacter->GetMovingLeft(), deltaTime, mMarioCharacter->GetMovementSpeed(), mMarioCharacter->GetJumpForce());
}

void Level2::Render()
{
	//mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	for (int y = 1; y <= mLoader->GetColumnSize(); y++)
	{
		for (int x = 0; x < mLoader->GetRowSize(); x++)
		{
			if (mLoader->GetTileAt(y, x) == '1')
			{
				//mBrickTexture->Render(Vector2D(x * 32.0f, (y-1) * 32.0f), SDL_FLIP_NONE);
			}
		}
	}
	//mMarioCharacter->Render();
};

bool Level2::SetUpLevel()
{
	//Create the level map
	SetLevelMap();


	mMarioCharacter = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap, mLoader);
	mBackgroundYPos = 0.0f;

	mBrickTexture = new Texture2D(mRenderer);
	if (!mBrickTexture->LoadFromFile("Images/Brick.png"))
	{
		cout << "Failed to load brick texture";
		return false;
	}
	return true;
	//mBackgroundTexture = new Texture2D(mRenderer);
	//if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	//{
	//	cout << "Failed to load background texture!";
	//	return false;
	//}
	//return true;
};

void Level2::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
									{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
									{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

	
	char ch;
	fstream fin("Maps/Map2.txt", fstream::in);

	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			char ch = fin.get();
			if (ch != '\n') map2[x][y] = ch;
		}
	}

	for (int x = 0; x < MAP_WIDTH; x++)
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			cout << map2[x][y];
		}
	}

	mLoader = new LevelLoader("Maps/Map2.txt");

	//Clear up any old map.
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//Set the new one
	mLevelMap = new LevelMap(map);

	//mCollisionManager = new BlockCollider(mLevelMap, mRenderer);
	mBetterCollisionManager = new BlockCollider2(mLoader, mRenderer);
	cout << "Collisions loaded" << endl;
}