#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Intro.h"
#include "End.h"

//Initialise the instance to null
GameScreenManager* GameScreenManager::mInstance = 0;

GameScreenManager::GameScreenManager()
{

}

void GameScreenManager::InitGameScreen(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = nullptr;

	//Set up first screen
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = nullptr;
	mCurrentScreen = NULL;
	delete mCurrentScreen;
}



GameScreenManager* GameScreenManager::Instance()
{
	if (!mInstance)
	{
		mInstance = new GameScreenManager();
	}
	return mInstance;
}

 void GameScreenManager::Render()
{
		mCurrentScreen->Render();
}

 void GameScreenManager::Update(float deltaTime, SDL_Event e)
 {
	 mCurrentScreen->Update(deltaTime, e);
 }

 void GameScreenManager::ChangeScreen(SCREENS newScreen)
 {
	 //Clear old screen
	 if (mCurrentScreen != nullptr)
	 {
		 delete mCurrentScreen;
	 }

	 GameScreenLevel1* tempScreen;
	 Level2* Screen2;
	 Level3* Screen3;
	 Level4* Screen4;
	 Intro* IntroScreen;
	 End* EndScreen;

	 switch (newScreen)
	 {
	 case SCREEN_LEVEL1:
	 {
		 // tempScreen = new GameScreenLevel1(mRenderer);
		 tempScreen = new GameScreenLevel1(mRenderer);
		 mCurrentScreen = (GameScreen*)tempScreen;
		 tempScreen = nullptr;
		 break;
	 }
	 case SCREEN_LEVEL2:
	 {
		 Screen2 = new Level2(mRenderer);
		 mCurrentScreen = (GameScreen*)Screen2;
		 Screen2 = nullptr;
		 break;
	 }
	  case SCREEN_LEVEL3:
	  {
		  Screen3 = new Level3(mRenderer);
		  mCurrentScreen = (GameScreen*)Screen3;
		  Screen3 = nullptr;
		  break;
	  }
	  case SCREEN_LEVEL4:
	  {
		  Screen4 = new Level4(mRenderer);
		  mCurrentScreen = (GameScreen*)Screen4;
		  Screen4 = nullptr;
		  break;
	  }
	  case SCREEN_INTRO:
	  {
		  IntroScreen = new Intro(mRenderer);
		  mCurrentScreen = (GameScreen*)IntroScreen;
		  IntroScreen = nullptr;
		  break;
	  }
	  case SCREEN_HIGHSCORES:
	  {
		  EndScreen = new End(mRenderer);
		  mCurrentScreen = (GameScreen*)EndScreen;
		  EndScreen = nullptr;
		  break;
	  }

 }
 }



