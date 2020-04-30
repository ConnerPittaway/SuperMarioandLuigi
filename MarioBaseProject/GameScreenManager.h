#pragma once
#include <SDL.h>
#include "Commons.h"

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager();
	~GameScreenManager();

	static GameScreenManager* Instance();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);

	void InitGameScreen(SDL_Renderer* renderer, SCREENS startScreen);

private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;
	static GameScreenManager* mInstance;
};

