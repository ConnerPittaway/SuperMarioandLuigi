#include "CharacterMario.h"



CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, LevelLoader* load) : Character(renderer, imagePath, startPosition, map)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mPosition = startPosition;
	mFacingDirection = FACING_RIGHT;
	mCollisionRadius = 15.0f;
	mCurrentLevelMap = map;
	mLoad = load;
	mMovementSpeed = MARIO_SPEED;
	if (!mTexture->LoadFromFile(imagePath))
	{
		cout << "Failed to load character texture" << endl;
	}
}

CharacterMario::~CharacterMario()
{
	mRenderer = nullptr;
}


void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	////Collision position variables
	//int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	//int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	//Collision position variables
	int centralXPosition = (int)(mPosition.x + ((mTexture->GetWidth()/4) * 0.5f)) / 16;
	int footPosition = (int)((mPosition.y + (mTexture->GetHeight()/2)) / 16) + 1;

	//Deal with jumping first
	if (mJumping)
	{
		//cout << footPosition << endl;

		//Adjust position
		mPosition.y -= mJumpForce * deltaTime;

		//Reduce force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		////Check if force is zero
		//if (mJumpForce <= 0.0f && (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 1) || mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 'f')
		//{
		//	mJumping = false;
		//	mCanJump = true;

		//}
		//Check if force is zero
		if (mJumpForce <= 0.0f && ((mLoad->GetTileAt(footPosition, centralXPosition) == 1) || mLoad->GetTileAt(footPosition, centralXPosition) == 'f'))
		{
			mJumping = false;
			mCanJump = true;

		}
	}

	////Deal with gravity
	//if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0 || mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == ' ')
	//{
	//	AddGravity(deltaTime);
	//}
	//else if ((mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 1) || mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 'f')
	//{
	//	//Collided with ground
	//	mCanJump = true;
	//}

	//Deal with gravity
	if (mLoad->GetTileAt(footPosition, centralXPosition) == ' ' || mLoad->GetTileAt(footPosition, centralXPosition) == 'c' || mLoad->GetTileAt(footPosition, centralXPosition) == 'e')
	{
		AddGravity(deltaTime);
	}
	else if (mLoad->GetTileAt(footPosition, centralXPosition) == 'f' || mLoad->GetTileAt(footPosition, centralXPosition) == 'b' 
		|| mLoad->GetTileAt(footPosition, centralXPosition) == 'y' || mLoad->GetTileAt(footPosition, centralXPosition) == 'z' || mLoad->GetTileAt(footPosition, centralXPosition) == 's')
	{
		//Collided with ground
		mCanJump = true;
	}

	if (mMovingLeft)
	{
		MoveLeft(deltaTime, mMovementSpeed);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime, mMovementSpeed);
	}

	//Handles any events
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
		{
			mMovingRight = true;
			SetMovingRight(true);
			break;
		}
		case SDLK_a:
		{
			mMovingLeft = true;
			SetMovingLeft(true);
			break;
		}
		case SDLK_SPACE:
		{
			mCurrentFrame = 0;
			Character::Jump();
			break;
		}
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
		{
			mMovingRight = false;
			SetMovingRight(false);
			break;
		}
		case SDLK_a:
		{
			mMovingLeft = false;
			SetMovingLeft(false);
			break;
		}
		}
	}
}

void CharacterMario::SmallJump()
{
	mJumpForce = JUMP_FORCE_HIT;
	mJumping = true;
	mCanJump = false;
}

void CharacterMario::Render(Camera* cam, float deltaTime)
{
	//Variable to hold the left position of the sprite we want to draw
	int mSingleSpriteWidth = 14;
	int y = 0;
	mSingleSpriteHeight = mTexture->GetHeight()/2;


	mFrameDelay -= deltaTime;

	if (!mJumping)
	{
		if (mFrameDelay <= 0.0f)
		{
			mFrameDelay = MARIO_DELAY;
			mCurrentFrame++;

			y = 0;
			if (mCurrentFrame > 3 || (GetMovingRight() == false && GetMovingLeft() == false))
				mCurrentFrame = 0;


		}
	}
	else
	{
		y = 1;
		mCurrentFrame = 1;
	}

	//If injured move the left position to be the left position of the second image on the spritesheet
	////if (mInjured)
	////	left = mSingleSpriteWidth;

	//Get the portion of the spritesheet to draw
	//								{XPos, YPos, WidthOfSprite, HeightOfSingleSprite}
	SDL_Rect portionOfSpritesheet = { mSingleSpriteWidth * mCurrentFrame, mSingleSpriteHeight*y, mSingleSpriteWidth, mSingleSpriteHeight};

	//Determine where you want it drawn
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	//Then draw it facing the correct direction
	if (GetDirection() == FACING_RIGHT)
	{
		mTexture->Render(cam, portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(cam, portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}