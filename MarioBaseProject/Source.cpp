#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "LevelLoader.h"
#include "GameScreenManager.h"
#include "Globals.h"


using namespace::std;



//Globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Texture2D* gTexture = NULL;
Mix_Music* gMusic = NULL;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void LoadMusic(string music);

LevelLoader* Load;

//Time
Uint32 gOldTime;

int main(int argc, char* args[])
{
	//Flag to check if wish to quit
	bool quit = false;

	if (InitSDL())
	{
		//LoadMusic("Music/Mario.mp3");
		//if (Mix_PlayingMusic() == 0)
		//{
		//	Mix_PlayMusic(gMusic, -1);
		//}

		GameScreenManager::Instance();
		GameScreenManager::Instance()->InitGameScreen(gRenderer, SCREEN_INTRO);

		Globals::Instance();
		Globals::Instance()->InitGlobals();

		//Set up the game screen manager - Start with Level1
		//gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL3);

		gOldTime = SDL_GetTicks();
	}
	//Game Loop
	while (!quit)
	{
		Render();

		quit = Update();
	}
	//Close Window and free resources
	CloseSDL();
	return 0;
}

bool InitSDL()
{
	

	if (TTF_Init() == -1)
		cout << "Error TTF " << TTF_GetError() << endl;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//All good, so attempt to create the window.
		gWindow = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		//Did the window get created?
		if (gWindow == NULL)
		{
			//Nope.
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer != NULL)
		{
			//Initialise PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not intialise. Error: " << IMG_GetError();
				return false;
			}

			//Load the background texture
			gTexture = new Texture2D(gRenderer);
			if (!gTexture->LoadFromFile("Images/test.bmp"))
			{
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}
		
	}
	




	return true;
}

bool Update()
{
	

	//Event Handler.
	SDL_Event e;

	//Get the events.
	SDL_PollEvent(&e);

	//Get new time
	Uint32 newTime = SDL_GetTicks();

	//Handles any events
	switch (e.type)
	{
		//Click the 'X' to quit.
	case SDL_QUIT:
		return true;
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_q:
			return true;
			break;
		}	
	}
	if (GameScreenManager::Instance() != NULL)
	GameScreenManager::Instance()->Update((float)(newTime - gOldTime) / 1000.0f, e);

	//Set the current time to be the old time
	gOldTime = newTime;

	return false;
}

void CloseSDL()
{
	//Release the renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Release the window.
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Release the texture
	delete gTexture;
	gTexture = NULL;


	//Delete Music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	//Quit SDL subsystems.
	IMG_Quit();
	SDL_Quit();
}

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	//gTexture->Render(Vector2D(), SDL_FLIP_NONE);
	if(GameScreenManager::Instance() != NULL)
	GameScreenManager::Instance()->Render();

	//Update the screen
	SDL_RenderPresent(gRenderer);
}

void LoadMusic(string music)
{
	////Load Music
	//gMusic = Mix_LoadMUS(music.c_str());

	//if (gMusic == NULL)
	//{
	//	cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	//}

}
