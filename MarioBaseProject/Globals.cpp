#include "Globals.h"

//Initialise the instance to null
Globals* Globals::mInstance = 0;

Globals* Globals::Instance() //Instance of global class
{
	if (!mInstance)
	{
		mInstance = new Globals();
	}
	return mInstance;
}

void Globals::InitGlobals()
{
	Score = 0;
	Lives = 3;
}

void Globals::SetScore(int scoreToAdd)
{
	Score += scoreToAdd;
}

int Globals::GetScore()
{
	return Score;
}

void Globals::SetLives(int lives)
{
	Lives += lives;
}

int Globals::GetLives()
{
	return Lives;
}


Globals::Globals()
{
}

Globals::~Globals()
{
}

