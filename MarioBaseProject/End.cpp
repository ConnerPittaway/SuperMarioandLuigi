#include "End.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "Constants.h"
#include "Camera.h"
#include <fstream>
#include <string>



End::End(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();

	mLevelMap = NULL;
}

End::~End()
{
	mBackgroundTexture = nullptr;
}

void End::Update(float deltaTime, SDL_Event e)
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
			Globals::Instance()->InitGlobals();
			GameScreenManager::Instance()->ChangeScreen(SCREEN_LEVEL3);
			break;
		}
		}
	}
}

void End::Render()
{

	//Get new time
	Uint32 newTime = SDL_GetTicks();


	mBackgroundTexture->Render(mCamera, (Vector2D(0, 0)), SDL_FLIP_NONE);

	string str1 = std::to_string(mScoreReaderWriter->scores[0]);
	string str2 = std::to_string(mScoreReaderWriter->scores[1]);
	string str3 = std::to_string(mScoreReaderWriter->scores[2]);
	string str4 = std::to_string(mScoreReaderWriter->scores[3]);
	string str5 = std::to_string(mScoreReaderWriter->scores[4]);

	SDL_Color color = { 255, 255, 255, 255 };

	mScore1->LoadRenderedText(str1, color);
	mScore1->Render(Vector2D(SCREEN_WIDTH/2 - 100, 40), SDL_FLIP_NONE);

	mScore2->LoadRenderedText(str2, color);
	mScore2->Render(Vector2D(SCREEN_WIDTH / 2 - 100, 70), SDL_FLIP_NONE);

	mScore3->LoadRenderedText(str3, color);
	mScore3->Render(Vector2D(SCREEN_WIDTH / 2 - 100, 100), SDL_FLIP_NONE);

	mScore4->LoadRenderedText(str4, color);
	mScore4->Render(Vector2D(SCREEN_WIDTH / 2 - 100, 130), SDL_FLIP_NONE);

	mScore5->LoadRenderedText(str5, color);
	mScore5->Render(Vector2D(SCREEN_WIDTH/2 - 100, 160), SDL_FLIP_NONE);

	mHighScoreText->LoadRenderedText("High Scores:", color);
	mHighScoreText->Render(Vector2D(SCREEN_WIDTH / 2 - 100, 10), SDL_FLIP_NONE);

	mPlayAgainText->LoadRenderedText("Press Space to play again!", color);
	mPlayAgainText->Render(Vector2D(SCREEN_WIDTH / 2 - 100, 250), SDL_FLIP_NONE);

	//Set the current time to be the old time
	gOldTime = newTime;
	//CurrentTime += (int)SDL_GetTicks();
	CurrentTime += gOldTime;
	CurrentTime = CurrentTime / 1000;
};

bool End::SetUpLevel()
{
	SDL_Rect textRect;
	textRect.x = 0; textRect.y = 0;


	mText = new Texture2D(mRenderer);
	mText->LoadFont("Font/SuperMario256.ttf");


	mScore1 = new Texture2D(mRenderer);
	mScore1->LoadFont("Font/SuperMario256.ttf");

	mScore2 = new Texture2D(mRenderer);
	mScore2->LoadFont("Font/SuperMario256.ttf");

	mScore3 = new Texture2D(mRenderer);
	mScore3->LoadFont("Font/SuperMario256.ttf");

	mScore4 = new Texture2D(mRenderer);
	mScore4->LoadFont("Font/SuperMario256.ttf");

	mScore5 = new Texture2D(mRenderer);
	mScore5->LoadFont("Font/SuperMario256.ttf");

	mHighScoreText = new Texture2D(mRenderer);
	mHighScoreText->LoadFont("Font/SuperMario256.ttf");

	mPlayAgainText = new Texture2D(mRenderer);
	mPlayAgainText->LoadFont("Font/SuperMario256.ttf");

	mBackgroundYPos = 0.0f;
	mSounds = new SoundEffects();
	mSounds->loadMusic();

	mCamera = new Camera();

	mScoreReaderWriter = new ScoreReaderWriter();
	mBackgroundTexture = new Texture2D(mRenderer);

	mScoreReaderWriter->InputScore(Globals::Instance()->GetScore());
	mScoreReaderWriter->ReadScores();
	mScoreReaderWriter->SortScores();
	mScoreReaderWriter->WriteScores();

	if (!mBackgroundTexture->LoadFromFile("Images/End.png"))
	{
		cout << "Failed to load background";
		return false;
	}
	return true;
};


