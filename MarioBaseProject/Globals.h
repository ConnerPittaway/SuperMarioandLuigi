#pragma once
#include <SDL.h>
#include "Commons.h"

class Globals
{
public:
	Globals();
	~Globals();

	static Globals* Instance();

	void InitGlobals();

	void SetScore(int scoreToAdd);
	int GetScore();

	void SetLives(int lives);
	int GetLives();


private:
	static Globals* mInstance;
	int Score;
	int Lives;
};
