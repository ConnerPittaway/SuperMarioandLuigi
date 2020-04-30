#pragma once
#include "SDL.h"
#include "Constants.h"
class Camera
{
public:

	Camera()
	{
		SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	};

	~Camera()
	{

	}

	SDL_Rect camera;
private:

};

