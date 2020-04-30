#pragma once
#include <SDL.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

enum Effects {
	COIN,
	JUMP,
	BUMP
};

class SoundEffects
{
private:
	Mix_Music* mMusic = NULL;
	Mix_Music* mUnderMusic = NULL;

	//Sound Effects
	Mix_Chunk* mBackgroundMusic;
	Mix_Chunk* mCoinCollect;
	Mix_Chunk* mJump;
	Mix_Chunk* mBump;


public:
	SoundEffects();
	~SoundEffects();
	bool loadMusic();
	void LoopBackground();
	void LoopUnderBackground();

	void PlaySoundEffect(Effects Soundeffect);

};

