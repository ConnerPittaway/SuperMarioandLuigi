#include "SoundEffects.h"
#include <iostream>

SoundEffects::SoundEffects()
{
	//Initialise the Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
	{
		std::cout << "Mixer could not initialise. Error: " << Mix_GetError() << std::endl;
	}
}

SoundEffects::~SoundEffects()
{
}

bool SoundEffects::loadMusic()
{
	//Load Music
	mMusic = Mix_LoadMUS("Music/Mario.mp3");

	if (mMusic == NULL)
	{
		std::cout << "Failed to load background music! Error: " << Mix_GetError() << std::endl;
	}

	//Load Music
	mUnderMusic = Mix_LoadMUS("Music/MarioUnderworld.mp3");

	if (mUnderMusic == NULL)
	{
		std::cout << "Failed to load background music! Error: " << Mix_GetError() << std::endl;
	}

	mCoinCollect = Mix_LoadWAV("Music/smw_coin.wav");
	if (mCoinCollect == NULL)
	{
		std::cout << "Failed to load coin music! Error: " << Mix_GetError() << std::endl;
	}


	mJump = Mix_LoadWAV("Music/smw_jump.wav");
	if (mJump == NULL)
	{
			std::cout << "Failed to load jump music! Error: " << Mix_GetError() << std::endl;
	}

	mBump = Mix_LoadWAV("Music/smb_bump.wav");
	if (mBump == NULL)
	{
		std::cout << "Failed to load bump music! Error: " << Mix_GetError() << std::endl;
	}
	return true;
}

void SoundEffects::LoopBackground()
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(mMusic, -1);
	}
}

void SoundEffects::LoopUnderBackground()
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(mUnderMusic, -1);
	}
}

void SoundEffects::PlaySoundEffect(Effects Soundeffect)
{
	switch (Soundeffect)
	{
	case COIN:
	{
		Mix_PlayChannel(-1, mCoinCollect, 0);
		return;
	}
	case JUMP:
	{
		Mix_PlayChannel(-1, mJump, 0);
		return;
	}
	case BUMP:
	{
		Mix_PlayChannel(-1, mBump, 0);
	}
	default:
		return;
	}
}

