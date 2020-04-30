#include "PowerBlock.h"



PowerBlock::PowerBlock(Camera* cam, SDL_Renderer* renderer, LevelLoader* load, Vector2D position)
{
	string imagePath = "Images/BlockSheet.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load texture: " << imagePath << endl;
		return;
	}

	mLoad = load;

	mSingleSpriteWidth = mTexture->GetWidth() / 4; //3 sprites on this spritesheet in 1 row.
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 1;
	mPosition = position;
	camera = cam;
}


PowerBlock::~PowerBlock()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLoad = NULL;
}

bool PowerBlock::IsAvaliable()
{
	return mNumberOfHitsLeft > 0;
}

Rect2D PowerBlock::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth()/4, mTexture->GetHeight());
}

void PowerBlock::TakeAHit()
{
	cout << mNumberOfHitsLeft << endl;
	mNumberOfHitsLeft--;
	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;
		mCurrentFrame = 3;
		//mLoad->ChangeTileAt(8, 7, 0);
		//mLoad->ChangeTileAt(8, 8, 0);
	}
	return;
}

void PowerBlock::Render(Camera* cam, float deltaTime)
{
	//Variable to hold the left position of the sprite we want to draw
	int y = mSingleSpriteHeight;

	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f)
	{
		mFrameDelay = BLOCK_DELAY;
		mCurrentFrame++;

		if (mCurrentFrame > 2)
			mCurrentFrame = 0;
	}

	if (mNumberOfHitsLeft > 0)
	{
		//
		SDL_Rect portionOfSpritesheet = { mSingleSpriteWidth * mCurrentFrame, 0, mSingleSpriteWidth, mSingleSpriteHeight };

		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

		mTexture->Render(cam, portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mCurrentFrame = 3;
		//
		SDL_Rect portionOfSpritesheet = { mSingleSpriteWidth * mCurrentFrame, 0, mSingleSpriteWidth, mSingleSpriteHeight };

		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

		mTexture->Render(cam, portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
}