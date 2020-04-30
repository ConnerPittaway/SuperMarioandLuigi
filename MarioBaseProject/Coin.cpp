#include "Coin.h"

Coin::Coin(Camera* cam, SDL_Renderer* renderer, LevelLoader* load, Vector2D position)
{
	string imagePath = "Images/CoinSheet.png";
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


Coin::~Coin()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLoad = NULL;
}

bool Coin::IsAvaliable()
{
	return mNumberOfHitsLeft > 0;
}

Rect2D Coin::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth() / 4, mTexture->GetHeight());
}

void Coin::TakeAHit()
{
	cout << mNumberOfHitsLeft << endl;
	mNumberOfHitsLeft--;
	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;
		//mLoad->ChangeTileAt(8, 7, 0);
		//mLoad->ChangeTileAt(8, 8, 0);
	}
	return;
}

void Coin::Render(Camera* cam, float deltaTime)
{
	//Variable to hold the left position of the sprite we want to draw
	int y = mSingleSpriteHeight;

	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f)
	{
		mFrameDelay = BLOCK_DELAY;
		mCurrentFrame++;

		if (mCurrentFrame > 3)
			mCurrentFrame = 0;
	}

	if (mNumberOfHitsLeft > 0)
	{
		//
		SDL_Rect portionOfSpritesheet = { mSingleSpriteWidth * mCurrentFrame, 0, mSingleSpriteWidth, mSingleSpriteHeight };

		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

		mTexture->Render(cam, portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
}