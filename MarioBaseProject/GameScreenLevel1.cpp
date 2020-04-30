#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	mLevelMap = NULL;
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete myCharacter;
	delete mPowBlock;
	delete mBackgroundTexture;
	delete CollisionManager;
	delete mLevelMap;
	mMarioCharacter = nullptr;
	mBackgroundTexture = nullptr;
	mPowBlock = nullptr;
	mEnemies.clear();
	
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//Screenshake Function
	if (mScreenshake)
	{
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		//End the shake after the duration
		if (mScreenshakeTime <= 0.0f)
		{
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	mMarioCharacter->Update(deltaTime, e);
	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);
	CheckCollision();
	//if (Collisions::Instance()->Circle(myCharacter, myCharacter2))
	{
	}
	if (Collisions::Instance()->Box(mMarioCharacter->GetCollisonBox(), myCharacter2->GetCollisonBox()))
	{
		//cout << "Collision";
	}
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(mMarioCharacter->GetCollisonBox(), mPowBlock->GetCollisionBox()) && mPowBlock->IsAvaliable())
	{
 		if (mMarioCharacter->IsJumping())
		{
			//cout << "cOLLIDE" << endl;
			DoScreenshake();
			if (!mEnemies.empty())
			{
				for (unsigned int i = 0; i < mEnemies.size(); i++)
				{
					mEnemies[i]->TakeDamage();
				}
			}
			mMarioCharacter->CancelJump();
			mPowBlock->TakeAHit();
			if (!mPowBlock->IsAvaliable())
			{
				
				//CollisionManager->UpdateCollisions(mLevelMap);
			}
		}
	}

	
}
void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	//Update Enemies

	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			//Check if enemy is on the bottom row of tiles
			if (mEnemies[i]->GetPosition().y > 300.0f)
			{
				//Is the enemy off the screen to left/right
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisonBox().width * 0.5f) || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisonBox().width * 0.55f))
				{
					mEnemies[i]->SetAlive(false);
				}
			}

			//Now update
			{
				mEnemies[i]->Update(deltaTime, e);

				//Check to see if the enemy collides with the player
				if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
				{
					//Ignore collision if enemy is behind a pipe
				}
				else
				{
					if (Collisions::Instance()->Circle(mEnemies[i], mMarioCharacter))
					{
						//mMarioCharacter->SetState(CHARACTERSTATE_PLAYER_DEATH);
						std::cout << "Koopa here " << std::endl;
						//mEnemies[i]->SetAlive(false);
					}
				}

				//If the enemy is no longer alive, then schedule for deletion
				if (mEnemies[i]->GetAlive() == false)
				{
					enemyIndexToDelete = i;
				}
			}

			//Remove dead enemies
			if (enemyIndexToDelete != -1)
			{
				mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
			}
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	//koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, Vector2D(position), direction, speed);
	//mEnemies.push_back(koopaCharacter);
}

void GameScreenLevel1::CheckCollision()
{
	CollisionManager->CheckCollision(mMarioCharacter);
}

void GameScreenLevel1::Render()
{
	//Draw the Enemies
	

	//mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	//myCharacter->Render();
	//mMarioCharacter->Render();
	//for (unsigned int i = 0; i < mEnemies.size(); i++)
	//{
	//	mEnemies[i]->Render(camer);
	//}
	//myCharacter2->Render();
	//mPowBlock->Render();
};

bool GameScreenLevel1::SetUpLevel()
{
	//Create the level map
	SetLevelMap();

	//Set up player character
	//myCharacter = new Character(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);
	myCharacter2 = new Character(mRenderer, "Images/Luigi.png", Vector2D(64, 32), mLevelMap);

	//mMarioCharacter = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330), mLevelMap);

	//Create Enemies
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	//Set up POW block
	//mPowBlock = new POWBlock(mRenderer, mLevelMap);


	CollisionManager = new BlockCollider(mLevelMap, mRenderer);

	//Screenshake
	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}
	return true;
};

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] ={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
									{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									{ 0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0},
									{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

	//Clear up any old map.
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//Set the new one
	mLevelMap = new LevelMap(map);


	////Set up collisions
	//for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	//{
	//	for (unsigned int j = 0; j < MAP_WIDTH; j++)
	//	{
	//		cout << mLevelMap->GetTileAt(i, j);
	//	}
	//}

}

void GameScreenLevel1::DoScreenshake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
}