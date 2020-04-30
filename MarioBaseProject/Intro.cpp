#include "Intro.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "Constants.h"
#include "Camera.h"
#include <fstream>
#include <string>



Intro::Intro(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();

	mLevelMap = NULL;
}

Intro::~Intro()
{
	mBackgroundTexture = nullptr;
}

void Intro::Update(float deltaTime, SDL_Event e)
{
	//Keep the camera in bounds
	if (mCamera->camera.x < 0)
	{
		mCamera->camera.x = 0;
	}
	if (mCamera->camera.y < 0)
	{
		mCamera->camera.y = 0;
	}
	//if (mCamera->camera.x > LEVEL_WIDTH - mCamera->camera.w)
	//{
	//	mCamera->camera.x = LEVEL_WIDTH - mCamera->camera.w;
	//}
	//if (mCamera->camera.y > LEVEL_HEIGHT - mCamera->camera.h)
	//{
	//	mCamera->camera.y = LEVEL_HEIGHT - mCamera->camera.h;
	//}
	mSounds->LoopBackground();

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
		{
			GameScreenManager::Instance()->ChangeScreen(SCREEN_LEVEL3);
			break;
		}
		}
	}
}

void Intro::Render()
{

	//Get new time
	Uint32 newTime = SDL_GetTicks();


	mBackgroundTexture->Render(mCamera, (Vector2D(0, 0)), SDL_FLIP_NONE);

	//Set the current time to be the old time
	gOldTime = newTime;
	//CurrentTime += (int)SDL_GetTicks();
	CurrentTime += gOldTime;
	CurrentTime = CurrentTime / 1000;
};

bool Intro::SetUpLevel()
{
	SDL_Rect textRect;
	textRect.x = 0; textRect.y = 0;


	mText = new Texture2D(mRenderer);
	mText->LoadFont("Font/SuperMario256.ttf");


	mBackgroundYPos = 0.0f;
	mSounds = new SoundEffects();
	mSounds->loadMusic();
	
	mCamera = new Camera();

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/Intro.png"))
	{
		cout << "Failed to load background";
		return false;
	}
	return true;
};


