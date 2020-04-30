#include "Level3.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "Constants.h"
#include "Camera.h"
#include <fstream>
#include <string>



Level3::Level3(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();

	mLevelMap = NULL;
}

Level3::~Level3()
{
	delete mBrickTexture;
	delete mLevelMap;
	delete mMarioCharacter;
	delete mLuigiCharacter;
	mBackgroundTexture = nullptr;
}

void Level3::Update(float deltaTime, SDL_Event e)
{

	mMarioCharacter->Update(deltaTime, e);
	if (mMarioCharacter->GetPosition().y - mMarioCharacter->GetCollisonBox().height > LEVEL_HEIGHT)
	{
		Globals::Instance()->SetLives(-1);
		GameScreenManager::Instance()->ChangeScreen(SCREEN_LEVEL3);
	}
	if (mMarioCharacter->IsJumping() && mMarioCharacter->GetJumpForce() == INITIAL_JUMP_FORCE)
	{
		mSounds->PlaySoundEffect(JUMP);
	}

	mLuigiCharacter->Update(deltaTime, e);
	if (mLuigiCharacter->IsJumping() && mLuigiCharacter->GetJumpForce() == INITIAL_JUMP_FORCE)
	{
		mSounds->PlaySoundEffect(JUMP);
	}

	mCamera->camera.x = (mMarioCharacter->GetPosition().x + mMarioCharacter->GetCollisonBox().width/2) - SCREEN_WIDTH/2;
	mCamera->camera.y = (mMarioCharacter->GetPosition().y + mMarioCharacter->GetCollisonBox().height/2) - SCREEN_HEIGHT;
	//Keep the camera in bounds
	if (mCamera->camera.x < 0)
	{
		mCamera->camera.x = 0;
	}
	if (mCamera->camera.y < 0)
	{
		mCamera->camera.y = 0;
	}
	if (mCamera->camera.x > LEVEL_WIDTH - mCamera->camera.w)
	{
		mCamera->camera.x = LEVEL_WIDTH - mCamera->camera.w;
	}
	if (mCamera->camera.y > LEVEL_HEIGHT - mCamera->camera.h)
	{
		mCamera->camera.y = LEVEL_HEIGHT - mCamera->camera.h;
	}
	UpdatePowerBlock();
	UpdateCoins();
	UpdateEnemies(deltaTime, e);
	mBetterCollisionManager->CheckCollision(mMarioCharacter, mMarioCharacter->GetMovingRight(), mMarioCharacter->GetMovingLeft(), deltaTime, mMarioCharacter->GetMovementSpeed(), mMarioCharacter->GetJumpForce());
	mBetterCollisionManager->CheckCollision(mLuigiCharacter, mLuigiCharacter->GetMovingRight(), mLuigiCharacter->GetMovingLeft(), deltaTime, mLuigiCharacter->GetMovementSpeed(), mLuigiCharacter->GetJumpForce());
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mBetterCollisionManager->CheckKoopaCollision(mEnemies[i], mEnemies[i]->GetMovingRight(), mEnemies[i]->GetMovingLeft());
	}
	UpdatePOWBlock();
	mSounds->LoopBackground();
	CheckWin();
	if (Globals::Instance()->GetLives() <= 0)
	{
		Globals::Instance()->InitGlobals();
		GameScreenManager::Instance()->ChangeScreen(SCREEN_INTRO);
	}
}

void Level3::Render()
{
	string Time = to_string(CurrentTime);
	SDL_Color color = { 255, 255, 255, 255 };
	mText->LoadRenderedText("Seconds: " + Time, color);
	mText->Render(Vector2D(0,5), SDL_FLIP_NONE);

	string ScoreText = to_string(Globals::Instance()->GetScore());
	mScoreText->LoadRenderedText("Score: " + ScoreText, color);
	mScoreText->Render(Vector2D(200, 5), SDL_FLIP_NONE);

	string LivesText = to_string(Globals::Instance()->GetLives());
	mScoreText->LoadRenderedText("Lives: " + LivesText, color);
	mScoreText->Render(Vector2D(400, 5), SDL_FLIP_NONE);

	//Get new time
	Uint32 newTime = SDL_GetTicks();


	mBackgroundTexture->Render(mCamera, (Vector2D(0,24)), SDL_FLIP_NONE);

	for (int y = 1; y <= mLoader->GetColumnSize(); y++)
	{
		for (int x = 0; x < mLoader->GetRowSize(); x++)
		{
			if (mLoader->GetTileAt(y, x) == 'b')
			{
				mBrickTexture->Render(mCamera, (Vector2D((x * 16), (y - 1) * 16)), SDL_FLIP_NONE);
			}
			else if (mLoader->GetTileAt(y, x) == 'f')
			{
				mFloorTexture->Render(mCamera, Vector2D(x * 16.0f, (y - 1) * 16.0f), SDL_FLIP_NONE);
			}
			else if (mLoader->GetTileAt(y, x) == 'w')
			{
				mBLPipeTexture->Render(mCamera, Vector2D(x * 16.0f, (y - 1) * 16.0f), SDL_FLIP_NONE);
			}
			else if (mLoader->GetTileAt(y, x) == 'x')
			{
				mBRPipeTexture->Render(mCamera, Vector2D(x * 16.0f, (y - 1) * 16.0f), SDL_FLIP_NONE);
			}
			else if (mLoader->GetTileAt(y, x) == 'y')
			{
				mTLPipeTexture->Render(mCamera, Vector2D(x * 16.0f, (y - 1) * 16.0f), SDL_FLIP_NONE);
			}
			else if (mLoader->GetTileAt(y, x) == 'z')
			{
				mTRPipeTexture->Render(mCamera, Vector2D(x * 16.0f, (y - 1) * 16.0f), SDL_FLIP_NONE);
			}
			else if (mLoader->GetTileAt(y, x) == 's')
			{
				mStairTexture->Render(mCamera, Vector2D(x * 16.0f, (y - 1) * 16.0f), SDL_FLIP_NONE);
			}
			else if (mLoader->GetTileAt(y, x) == 'g')
			{
				mPoleTexture->Render(mCamera, Vector2D(x * 16.0f, (y - 1) * 16.0f), SDL_FLIP_NONE);
			}
			else if (mLoader->GetTileAt(y, x) == 't')
			{
				mTopTexture->Render(mCamera, Vector2D(x * 16.0f, (y - 1) * 16.0f), SDL_FLIP_NONE);
			}
			else 
			{

			}
		}
	}
	mpowBlock->Render(mCamera);
	mMarioCharacter->Render(mCamera, (float)(newTime - gOldTime) / 1000.0f);
	mLuigiCharacter->Render(mCamera, (float)(newTime - gOldTime) / 1000.0f);
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render(mCamera, (float)(newTime - gOldTime) / 1000.0f);
	}

	for (unsigned int i = 0; i < mPowerBlocks.size(); i++)
	{
		mPowerBlocks[i]->Render(mCamera, (float)(newTime - gOldTime) / 1000.0f);
	}

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render(mCamera, (float)(newTime - gOldTime) / 1000.0f);
	}
	//Set the current time to be the old time
	gOldTime = newTime;
	//CurrentTime += (int)SDL_GetTicks();
	CurrentTime += gOldTime;
	CurrentTime = CurrentTime / 1000;


};

bool Level3::SetUpLevel()
{
	//Create the level map
	SetLevelMap();



	SDL_Rect textRect;
	textRect.x = 0; textRect.y = 0;


	mText = new Texture2D(mRenderer);
	mText->LoadFont("Font/SuperMario256.ttf");

	mScoreText = new Texture2D(mRenderer);
	mScoreText->LoadFont("Font/SuperMario256.ttf");


	mLivesText = new Texture2D(mRenderer);
	mLivesText->LoadFont("Font/SuperMario256.ttf");

	mpowBlock = new POWBlock(mCamera, mRenderer, mLevelMap, mLoader, Vector2D(500, 150));

	mMarioCharacter = new CharacterMario(mRenderer, "Images/MarioSheet2.png", Vector2D(32, 100), mLevelMap, mLoader);
	mLuigiCharacter = new CharacterLuigi(mRenderer, "Images/LuigiSheet.png", Vector2D(32, 100), mLevelMap, mLoader);
	mBackgroundYPos = 0.0f;
	mSounds = new SoundEffects();
	mSounds->loadMusic();
	//Create Enemies and Blocks
	for (int y = 1; y <= mLoader->GetColumnSize(); y++)
	{
		for (int x = 0; x < mLoader->GetRowSize(); x++)
		{
			if (mLoader->GetTileAt(y, x) == 'k')
			{
				int randNum = rand() % 2;
				FACING direction;
				if (randNum = 0)
				{
					direction = FACING_LEFT;
				}
				else
				{
					direction = FACING_RIGHT;
				}
				CreateKoopa(Vector2D((x*16), (y-1)*16), FACING_LEFT, KOOPA_SPEED);
			}
			else if (mLoader->GetTileAt(y, x) == 'p')
			{
				CreatePowerBlock(Vector2D((x * 16), (y - 1) * 16));
			}
			else if (mLoader->GetTileAt(y, x) == 'c')
			{
				CreateCoins(Vector2D((x * 16), (y - 1) * 16));
			}
		}
	}

	mCamera = new Camera();

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/MarioBackground.png"))
	{
		cout << "Failed to load background";
		return false;
	}

	mBrickTexture = new Texture2D(mRenderer);
	if (!mBrickTexture->LoadFromFile("Tiles/Level1/b.png"))
	{
		cout << "Failed to load brick texture";
		return false;
	}

	mFloorTexture = new Texture2D(mRenderer);
	if (!mFloorTexture->LoadFromFile("Tiles/Level1/f.png"))
	{
		cout << "Failed to load floor texture";
		return false;
	}

	mStairTexture = new Texture2D(mRenderer);
	if (!mStairTexture->LoadFromFile("Tiles/Level1/s.png"))
	{
		cout << "Failed to load stair texture";
		return false;
	}

	mBLPipeTexture = new Texture2D(mRenderer);
	if (!mBLPipeTexture->LoadFromFile("Tiles/Level1/w.png"))
	{
		cout << "Failed to load bl pipe texture";
		return false;
	}

	mBRPipeTexture = new Texture2D(mRenderer);
	if (!mBRPipeTexture->LoadFromFile("Tiles/Level1/x.png"))
	{
		cout << "Failed to load br pipe texture";
		return false;
	}

	mTLPipeTexture = new Texture2D(mRenderer);
	if (!mTLPipeTexture->LoadFromFile("Tiles/Level1/y.png"))
	{
		cout << "Failed to load tl pipe texture";
		return false;
	}

	mTRPipeTexture = new Texture2D(mRenderer);
	if (!mTRPipeTexture->LoadFromFile("Tiles/Level1/z.png"))
	{
		cout << "Failed to load tr pipe texture";
		return false;
	}

	mPoleTexture = new Texture2D(mRenderer);
	if (!mPoleTexture->LoadFromFile("Tiles/Level1/g.png"))
	{
		cout << "Failed to load pole texture";
		return false;
	}

	mPowerTexture = new Texture2D(mRenderer);
	if (!mPowerTexture->LoadFromFile("Tiles/Level1/p.png"))
	{
		cout << "Failed to load power texture";
		return false;
	}

	mTopTexture = new Texture2D(mRenderer);
	if (!mTopTexture->LoadFromFile("Tiles/Level1/t.png"))
	{
		cout << "Failed to load top texture";
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

void Level3::SetLevelMap()
{
	mLoader = new LevelLoader("Maps/1.txt");



	//Clear up any old map.
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//mCollisionManager = new BlockCollider(mLevelMap, mRenderer);
	mBetterCollisionManager = new BlockCollider3(mLoader, mRenderer);
	cout << "Collisions loaded" << endl;
}

void Level3::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopaCharacter = new CharacterKoopa(mCamera, mRenderer, "Images/KoopaSheet.png", mLevelMap, mLoader, Vector2D(position), direction, speed);
	mEnemies.push_back(koopaCharacter);
}

void Level3::CreatePowerBlock(Vector2D position)
{
	powerBlock = new PowerBlock(mCamera, mRenderer, mLoader, position);
	mPowerBlocks.push_back(powerBlock);
}

void Level3::CreateCoins(Vector2D position)
{
	coin = new Coin(mCamera, mRenderer, mLoader, position);
	mCoins.push_back(coin);
}


void Level3::UpdatePowerBlock()
{

	if (!mPowerBlocks.empty())
	{
		for (unsigned int i = 0; i < mPowerBlocks.size(); i++)
		{
			if (Collisions::Instance()->Box(mMarioCharacter->GetCollisonBox(), mPowerBlocks.at(i)->GetCollisionBox()) && mPowerBlocks.at(i)->IsAvaliable())
			{
				if (mMarioCharacter->IsJumping() && mMarioCharacter->GetCollisonBox().y > mPowerBlocks.at(i)->GetCollisionBox().y)
				{
					cout << "Block Collide " + i << endl;
					CreateCoins(Vector2D(mPowerBlocks.at(i)->GetCollisionBox().x, mPowerBlocks.at(i)->GetCollisionBox().y - 16.0f));
					//DoScreenshake();
					mSounds->PlaySoundEffect(BUMP);
					mMarioCharacter->CancelJump();
					mPowerBlocks.at(i)->TakeAHit();
					if (!mpowBlock->IsAvaliable())
					{

						//CollisionManager->UpdateCollisions(mLevelMap);
					}
				}
			}
			else if (Collisions::Instance()->Box(mLuigiCharacter->GetCollisonBox(), mPowerBlocks.at(i)->GetCollisionBox()) && mPowerBlocks.at(i)->IsAvaliable())
			{
				if (mLuigiCharacter->IsJumping() && mLuigiCharacter->GetCollisonBox().y > mPowerBlocks.at(i)->GetCollisionBox().y)
				{
					cout << "Block Collide " + i << endl;
					CreateCoins(Vector2D(mPowerBlocks.at(i)->GetCollisionBox().x, mPowerBlocks.at(i)->GetCollisionBox().y - 16.0f));
					//DoScreenshake();
					mSounds->PlaySoundEffect(BUMP);
					mLuigiCharacter->CancelJump();
					mPowerBlocks.at(i)->TakeAHit();
					if (!mpowBlock->IsAvaliable())
					{

						//CollisionManager->UpdateCollisions(mLevelMap);
					}
				}
			}
		}
	}
}

void Level3::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(mMarioCharacter->GetCollisonBox(), mpowBlock->GetCollisionBox()) && mpowBlock->IsAvaliable())
	{
		if (mMarioCharacter->IsJumping())
		{
			//cout << "cOLLIDE" << endl;
			//DoScreenshake();
			if (!mEnemies.empty())
			{
				for (unsigned int i = 0; i < mEnemies.size(); i++)
				{
					mEnemies[i]->TakeDamage();
				}
			}
			mMarioCharacter->CancelJump();
			mpowBlock->TakeAHit();
			if (!mpowBlock->IsAvaliable())
			{

			}
		}
	}
	else if (Collisions::Instance()->Box(mLuigiCharacter->GetCollisonBox(), mpowBlock->GetCollisionBox()) && mpowBlock->IsAvaliable())
	{
		if (mLuigiCharacter->IsJumping())
		{
			//cout << "cOLLIDE" << endl;
			//DoScreenshake();
			if (!mEnemies.empty())
			{
				for (unsigned int i = 0; i < mEnemies.size(); i++)
				{
					mEnemies[i]->TakeDamage();
				}
			}
			mLuigiCharacter->CancelJump();
			mpowBlock->TakeAHit();
			if (!mpowBlock->IsAvaliable())
			{

			}
		}
	}
}


void Level3::UpdateEnemies(float deltaTime, SDL_Event e)
{
	//Update Enemies

	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			//Now update
			{
				mEnemies[i]->Update(deltaTime, e);
					if (Collisions::Instance()->Circle(mEnemies[i], mMarioCharacter))
					{
						if (mMarioCharacter->GetCollisonBox().y + mMarioCharacter->GetCollisonBox().height < mEnemies[i]->GetKoopaCollisionBox().y + mEnemies[i]->GetKoopaCollisionBox().height/2 && mEnemies[i]->GetInjured() == false)
						{
							mMarioCharacter->SmallJump();
							//mMarioCharacter->SetState(CHARACTERSTATE_PLAYER_DEATH);
							mEnemies[i]->SetInjured(true);
							std::cout << "Koopa here " << std::endl;
							//mEnemies[i]->SetAlive(false);
						}
						else if (mMarioCharacter->GetCollisonBox().y + mMarioCharacter->GetCollisonBox().height < mEnemies[i]->GetKoopaCollisionBox().y + mEnemies[i]->GetKoopaCollisionBox().height / 2 && mEnemies[i]->GetInjured() == true)
						{
							mMarioCharacter->SmallJump();
							mEnemies[i]->SetAlive(false);
							Globals::Instance()->SetScore(100);
						}
					}
					else if (Collisions::Instance()->Circle(mEnemies[i], mLuigiCharacter))
					{
						if (mLuigiCharacter->GetCollisonBox().y + mLuigiCharacter->GetCollisonBox().height < mEnemies[i]->GetKoopaCollisionBox().y + mEnemies[i]->GetKoopaCollisionBox().height / 2 && mEnemies[i]->GetInjured() == false)
						{
							mLuigiCharacter->SmallJump();
							//mMarioCharacter->SetState(CHARACTERSTATE_PLAYER_DEATH);
							mEnemies[i]->SetInjured(true);
							std::cout << "Koopa here " << std::endl;
							//mEnemies[i]->SetAlive(false);
						}
						else if (mLuigiCharacter->GetCollisonBox().y + mLuigiCharacter->GetCollisonBox().height < mEnemies[i]->GetKoopaCollisionBox().y + mEnemies[i]->GetKoopaCollisionBox().height / 2 && mEnemies[i]->GetInjured() == true)
						{
							mLuigiCharacter->SmallJump();
							mEnemies[i]->SetAlive(false);
							Globals::Instance()->SetScore(100);
						}
					}
				}
				
			//Is the enemy off the screen to left/right
			if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisonBox().width * 0.5f) || mEnemies[i]->GetPosition().x > LEVEL_WIDTH - (float)(mEnemies[i]->GetKoopaCollisionBox().width * 0.55f))
			{
				cout << "Enemy died" << endl;
				mEnemies[i]->SetAlive(false);
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

void Level3::UpdateCoins()
{
	if (!mCoins.empty())
	{
		for (unsigned int i = 0; i < mCoins.size(); i++)
		{
			if (Collisions::Instance()->Box(mMarioCharacter->GetCollisonBox(), mCoins.at(i)->GetCollisionBox()) && mCoins.at(i)->IsAvaliable())
			{
					cout << "Block Collide " + i << endl;
					Globals::Instance()->SetScore(100);
					mSounds->PlaySoundEffect(COIN);
					mCoins.at(i)->TakeAHit();
					if (!mCoins.at(i)->IsAvaliable())
					{

						//CollisionManager->UpdateCollisions(mLevelMap);
					}
			}
			else if (Collisions::Instance()->Box(mLuigiCharacter->GetCollisonBox(), mCoins.at(i)->GetCollisionBox()) && mCoins.at(i)->IsAvaliable())
			{
				cout << "Block Collide " + i << endl;
				Globals::Instance()->SetScore(100);
				mSounds->PlaySoundEffect(COIN);
				mCoins.at(i)->TakeAHit();
				if (!mCoins.at(i)->IsAvaliable())
				{

					//CollisionManager->UpdateCollisions(mLevelMap);
				}
			}
		}
	}
}

bool Level3::CheckWin()
{
	if ((mLoader->GetTileAt(mMarioCharacter->GetPosition().y / 16, mMarioCharacter->GetPosition().x / 16) == 'g' || mLoader->GetTileAt(mMarioCharacter->GetPosition().y / 16, mMarioCharacter->GetPosition().x / 16) == 't'))
	{
		cout << "Win" << endl;
		GameScreenManager::Instance()->ChangeScreen(SCREENS::SCREEN_LEVEL4);
		return true;
	}
	else if ((mLoader->GetTileAt(mLuigiCharacter->GetPosition().y / 16, mLuigiCharacter->GetPosition().x / 16) == 'g' || mLoader->GetTileAt(mLuigiCharacter->GetPosition().y / 16, mLuigiCharacter->GetPosition().x / 16) == 't'))
	{
		cout << "Win" << endl;
		GameScreenManager::Instance()->ChangeScreen(SCREENS::SCREEN_LEVEL4);
		return true;
	}
	//else if ((mLoader->GetTileAt(mMarioCharacter->GetPosition().x, mMarioCharacter->GetPosition().y) == 'f' || mLoader->GetTileAt(mMarioCharacter->GetPosition().x, mMarioCharacter->GetPosition().y) == 't'))
	//{
	//	cout << "Floor" << endl;
	//}
}
