#include "Texture2D.h"
#include "Commons.h"
#include <SDL_image.h>
#include <iostream>
#include "Camera.h"

using namespace::std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;

}

int Texture2D::GetWidth()
{
	return mWidth;
}

int Texture2D::GetHeight()
{
	return mHeight;
}

void Texture2D::SetPosition(int posx, int posy)
{
	position.x = posx;
	position.y = posy;
}

Texture2D::~Texture2D()
{
	Free();
	mRenderer = NULL;
}

void Texture2D::Free()
{
	//Check if the texture exists before removing it
	if (mTexture != NULL)
	{
		//cout << "Deleted" << endl;
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mHeight = 0;
		mWidth = 0;
	}
}

void Texture2D::Render(Camera* cam, Vector2D newPosition, SDL_RendererFlip flip, double angle)
{

	newPosition.x -= cam->camera.x;
	newPosition.y -= cam->camera.y;
	//Set where to render the texture
	SDL_Rect renderLocation = { newPosition.x ,newPosition.y,mWidth,mHeight };

	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	//Set where to render the texture
	SDL_Rect renderLocation = { newPosition.x ,newPosition.y,mWidth,mHeight };

	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);
}

void Texture2D::Render(Camera* cam, SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	float newPositionx =destRect.x - cam->camera.x;
	float newPositiony = destRect.y - cam->camera.y;
	SDL_Rect renderLocation = { newPositionx ,newPositiony,srcRect.w,srcRect.h };
	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &renderLocation, angle, NULL, flip);
}

bool Texture2D::LoadFromFile(string path)
{
	//Remove the memory used for a previous texture.
	Free();

	// Assigning to null pointer
	//mTexture = nullptr;

	//Load the image
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{

		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));

		//Create the texture from the pixels on the surface
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		
		//Set Dimensions
		mWidth = pSurface->w;
		mHeight = pSurface->h;

		//Remove the loaded surface now that we have the texture
		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError() << endl;
	}

	//Return the texture
	return mTexture !=NULL;
}

bool Texture2D::LoadFont(string fontLocation)
{
	if (fontLocation != "")
	{
		mFont = TTF_OpenFont(fontLocation.c_str(), 16);
		if (mFont == NULL)
		{
			printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		}
	}
	return true;
}

bool Texture2D::LoadRenderedText(string textureText, SDL_Color textColor)
{
	Free();

	//Surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		cout << "Unable to render text surface" << endl;
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from rendered text" << endl;
		}
		else
		{
			//Set Dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}

