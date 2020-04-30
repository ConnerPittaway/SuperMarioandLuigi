#include "BlockCollider.h"

BlockCollider::BlockCollider(LevelMap* map, SDL_Renderer* renderer)
{
	mLevelMap = map;

	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			if (mLevelMap->GetTileAt(i, j) == 1)
			{
				SDL_Rect RectToDraw;
				RectToDraw.y = i * 32;
				RectToDraw.x = j * 32;
				RectToDraw.w = TILE_WIDTH;
				RectToDraw.h = TILE_HEIGHT;
				SDL_SetRenderDrawColor(renderer, 255, 0, 200, 255);
				SDL_RenderFillRect(renderer, &RectToDraw);

				mCollisionBox = &Rect2D(j * 32, i * 32, TILE_WIDTH, TILE_HEIGHT);
				mCollisionBoxes.push_back(*mCollisionBox);
				
				cout << mCollisionBox->x << endl;
				cout << mCollisionBox->y << endl;
				cout << mCollisionBox->width << endl;
				cout << mCollisionBox->height << endl;
			}
		}
	}
}

BlockCollider::~BlockCollider()
{
	mLevelMap = NULL;
}

void BlockCollider::UpdateCollisions(LevelMap* map)
{
	mLevelMap = map;
	mCollisionBoxes.clear();
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			if (mLevelMap->GetTileAt(i, j) == 1)
			{
				mCollisionBox = &Rect2D(j * 32, i * 32, TILE_WIDTH, TILE_HEIGHT);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << mCollisionBox->x << endl;
				cout << mCollisionBox->y << endl;
				cout << mCollisionBox->width << endl;
				cout << mCollisionBox->height << endl;
			}
		}
	}
}

bool BlockCollider::CheckCollision(Character* character)
{
	for (int i = 0; i < mCollisionBoxes.size(); i++)
	{
		if (Collisions::Instance()->Box(character->GetCollisonBox(), GetCollisionBox(i)))
		{
			if (character->IsJumping() && character->GetDirection() == FACING_LEFT)
			{
				character->CancelJump();
				cout << "Just Jump" << endl;
				character->SetPosition(Vector2D(character->GetPosition().x + 1, character->GetPosition().y + 1));
				return true;
			}
			else if (character->IsJumping() && character->GetDirection() == FACING_RIGHT)
			{
				character->CancelJump();
				cout << "Just Jump" << endl;
				character->SetPosition(Vector2D(character->GetPosition().x , character->GetPosition().y + 1));
				return true;
			}
			else if (character->GetDirection() == FACING_LEFT && !character->IsJumping())
			{
				//character->SetPosition(Vector2D(character->GetPosition().x + 0.1f, character->GetPosition().y));
				character->SetPosition(Vector2D(GetCollisionBox(i).x + (GetCollisionBox(i).width/2) + 0.1f, character->GetPosition().y));
				cout << "No Jump" << endl;
				return true;
			}
			else if (character->GetDirection() == FACING_RIGHT && !character->IsJumping())
			{
				character->SetPosition(Vector2D(GetCollisionBox(i).x - (GetCollisionBox(i).width / 2) - 0.1f, character->GetPosition().y));
				cout << "No Jump" << endl;
				return true;
			}
			cout << "Collision with " <<  i << " box at " << GetCollisionBox(i).x << " " << GetCollisionBox(i).y << endl << "Mario is at " << character->GetCollisonBox().x << " " << character->GetCollisonBox().y << endl;
			return true;
		}
	}
	return false;
}

Rect2D BlockCollider::GetCollisionBox(int n)
{
	return Rect2D(mCollisionBoxes[n].x, mCollisionBoxes[n].y, mCollisionBoxes[n].width, mCollisionBoxes[n].height);
}

void BlockCollider::LoadCollisions()
{

}
