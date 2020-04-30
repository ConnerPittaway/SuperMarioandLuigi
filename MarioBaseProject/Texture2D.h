#pragma once
#ifndef  _TEXTURE2D_H
#define _TEXTURE2D_H
#include "SDL.h"
#include <SDL_ttf.h>
#include "Commons.h"
#include "Camera.h"
#include <iostream>
using namespace::std;

class Texture2D
{
public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(string path);
	bool LoadFont(string fontLocation);
	bool LoadRenderedText(string textureText, SDL_Color textColor);
	void Free();
	void Render(Camera* cam, SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle = 0.0f);
	void Render(Camera* cam, Vector2D newPosition, SDL_RendererFlip flip, double angle = 0.0f);
	void Render(Vector2D newPosition, SDL_RendererFlip flip, double angle = 0.0f);

	int GetWidth();
	int GetHeight();

	void SetPosition(int posx, int posy);
	Vector2D GetPosition();
private:
	SDL_Renderer* mRenderer = nullptr;
	SDL_Texture* mTexture = nullptr;
	TTF_Font* mFont = nullptr;

	
	int mWidth;
	int mHeight;
	Vector2D position;
};

#endif _TEXTURE2D_H
