#include "POWBlock.h"



POWBlock::POWBlock(Camera* cam, SDL_Renderer* renderer, LevelMap* map, LevelLoader* load, Vector2D position)
{
	string imagePath = "Images/PowBlockSheet.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load texture: " << imagePath << endl;
		return;
	}

	mLevelMap = map;
	mLoad = load;

	mSingleSpriteWidth = mTexture->GetWidth() / 3; //3 sprites on this spritesheet in 1 row.
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = position;
}

POWBlock::~POWBlock()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLevelMap = NULL;
}

bool POWBlock::IsAvaliable()
{
	return mNumberOfHitsLeft > 0;
}

Rect2D POWBlock::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth()/3, mTexture->GetHeight());
}

void POWBlock::TakeAHit()
{
	cout << mNumberOfHitsLeft << endl;
	mNumberOfHitsLeft--;
	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;
		//mLevelMap->ChangeTileAt(8, 7, 0);
		//mLevelMap->ChangeTileAt(8, 8, 0);
	}
	return;
}

void POWBlock::Render(Camera* cam)
{
	if (mNumberOfHitsLeft > 0)
	{
		//Get the portion of the spritesheet you want to draw.
		int left = mSingleSpriteWidth * (3 - mNumberOfHitsLeft);

		//
		SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

		mTexture->Render(cam, portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
}

