#include "CharacterKoopa.h"



CharacterKoopa::CharacterKoopa(Camera* cam, SDL_Renderer* renderer, std::string imagePath, LevelMap* map, LevelLoader* load, Vector2D startPosition, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;
	mCurrentLevelMap = map;
	mLoad = load;
	camera = cam;
	if (!mTexture->LoadFromFile(imagePath))
	{
		cout << "Failed to load character texture" << endl;
	}

	mSingleSpriteWidth = mTexture->GetWidth(); 
	mSingleSpriteHeight = mTexture->GetHeight();
}


CharacterKoopa::~CharacterKoopa()
{
}

void CharacterKoopa::Render(Camera* cam, float deltaTime)
{
	//Variable to hold the left position of the sprite we want to draw
	int mSingleSpriteWidth = 16;
	int mSingleSpriteHeight = 16;
	int y = 0;



	mFrameDelay -= deltaTime;

	if (!mInjured)
	{
		if (mFrameDelay <= 0.0f)
		{
			mFrameDelay = ANIMATION_DELAY;
			mCurrentFrame++;

			if (mCurrentFrame > 1)
				mCurrentFrame = 0;
		}
	}
	else
	{
		y = 1;
		mCurrentFrame = 0;
	}

	//Get the portion of the spritesheet to draw
	//								{XPos, YPos, WidthOfSprite, HeightOfSingleSprite}
	SDL_Rect portionOfSpritesheet = {mSingleSpriteWidth*mCurrentFrame, mSingleSpriteHeight*y, mSingleSpriteWidth, mSingleSpriteHeight};

	//Determine where you want it drawn
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	//Then draw it facing the correct direction
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(cam ,portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(cam, portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	//To gain the benefit of the code written in the base class Update() function we need to call it
	Character::Update(deltaTime, e, KOOPA_SPEED);
	//Collision position variables
	int centralXPosition = (int)(mPosition.x + ((mTexture->GetWidth()/2) * 0.5f)) / 16;
	int footPosition = (int)((mPosition.y + (mTexture->GetHeight()/2)) / 16) + 1;
	//Deal with jumping first
	if (mJumping)
	{

		//cout << mJumpForce << endl;

		//Adjust position
		mPosition.y -= mJumpForce * deltaTime;

		//Reduce force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		//Check if force is zero
		if (mJumpForce <= 0.0f && (mLoad->GetTileAt(footPosition, centralXPosition) == 'f'))
		{
			mJumping = false;
			mCanJump = true;

		}

	}


	//Deal with gravity
	if (mLoad->GetTileAt(footPosition, centralXPosition) == ' ' || mLoad->GetTileAt(footPosition, centralXPosition) == 'n')
	{
		AddGravity(deltaTime);
	}
	else if (mLoad->GetTileAt(footPosition, centralXPosition) == 'f' || mLoad->GetTileAt(footPosition, centralXPosition) == 'b'
		|| mLoad->GetTileAt(footPosition, centralXPosition) == 'y' || mLoad->GetTileAt(footPosition, centralXPosition) == 'z' || mLoad->GetTileAt(footPosition, centralXPosition) == 's')
	{
		//Collided with ground
		mCanJump = true;
	}

	if (!mInjured)
	{
		//We are not injured so move
		if (Character::GetDirection() == FACING_LEFT)
		{
			SetMovingLeft(true);
			SetMovingRight(false);
		}
		else if (Character::GetDirection() == FACING_RIGHT)
		{
			//We should not be moving when injured
			SetMovingRight (true);
			SetMovingLeft(false);
		}
	}
	else
	{
		//We should not be moving when injured
		SetMovingRight(false);
		SetMovingLeft(false);

		//Count down the injured time
		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0)
		{
			FlipRightwayUp();
			mInjuredTime = 2.5f;
		}
	}

	if (GetMovingLeft()==true)
	{
		MoveLeft(deltaTime, mMovementSpeed);
	}
	else if (GetMovingRight()==true)
	{
		MoveRight(deltaTime, mMovementSpeed);
	}

}

Rect2D CharacterKoopa::GetKoopaCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y - 1, mTexture->GetWidth()/2, mTexture->GetHeight()/2);
}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = 2.5f;
	CharacterKoopa::Jump();
}

void CharacterKoopa::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;

		mJumping = true;
		mCanJump = false;

	}
}

void CharacterKoopa::FlipRightwayUp()
{
	if (mFacingDirection == FACING_LEFT)
	{
		mFacingDirection = FACING_RIGHT;
	}
	else
	{
		mFacingDirection = FACING_LEFT;
	}
	mInjured = false;
	CharacterKoopa::Jump();
}