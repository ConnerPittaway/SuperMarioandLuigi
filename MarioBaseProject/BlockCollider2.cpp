#include "BlockCollider2.h"

BlockCollider2::BlockCollider2(LevelLoader* map, SDL_Renderer* renderer)
{
	for (unsigned int y = 1; y < map->GetColumnSize(); y++)
	{
		for (unsigned int x = 0; x < map->GetRowSize(); x++)
		{
			if (map->GetTileAt(y, x) == '1')
			{
				mCollisionBox = new Rect2D((x) * 32, (y-1) * 32, TILE_WIDTH, TILE_HEIGHT);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << "x: " << mCollisionBox->x;
				cout << " " << "y: " <<mCollisionBox->y << endl;
			}
		}
	}
}

BlockCollider2::~BlockCollider2()
{
	LevMap = NULL;
}

void BlockCollider2::UpdateCollisions(LevelLoader* map)
{
	mCollisionBoxes.clear();
	for (unsigned int y = 1; y < map->GetColumnSize(); y++)
	{
		for (unsigned int x = 0; x < map->GetRowSize(); x++)
		{
			if (map->GetTileAt(y, x) == '1')
			{
				mCollisionBox = new Rect2D(x * 32, (y-1) * 32, TILE_WIDTH, TILE_HEIGHT);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << "x: " <<  mCollisionBox->x;
				cout << " " << "y: " << mCollisionBox->y << endl;
				cout << mCollisionBox->width << endl;
				cout << mCollisionBox->height << endl;
			}
		}
	}
}

bool BlockCollider2::CheckCollision(Character* character, bool right, bool left, float deltaTime, float speed, float jump)
{
	for (int i = 0; i < mCollisionBoxes.size(); i++)
	{
  		if (Collisions::Instance()->Box(character->GetCollisonBox(), mCollisionBoxes.at(i)))
		{
			if (!character->IsJumping() && left)
			{
				if ((character->GetCollisonBox().x - 0.000001f < mCollisionBoxes.at(i).x + mCollisionBoxes.at(i).width))
				{
					character->SetPosition(Vector2D(character->GetPosition().x + (speed * deltaTime), character->GetPosition().y));
					cout << "Right Side" << endl;
				}
					

				if ((character->GetCollisonBox().x + character->GetCollisonBox().width) + 0.000001f < mCollisionBoxes.at(i).x)
				{
					character->SetPosition(Vector2D(character->GetPosition().x - (speed * deltaTime), character->GetPosition().y));
				}
					
				cout << "Just move" << endl;
				cout << "x: " << mCollisionBoxes.at(i).x;
				cout << " " << "y: " << mCollisionBoxes.at(i).y << endl;
				return true;
			}
			else if (!character->IsJumping() && right)
			{
				if ((character->GetCollisonBox().x + character->GetCollisonBox().width) + 0.000001f > mCollisionBoxes.at(i).x)
				{
					character->SetPosition(Vector2D(character->GetPosition().x - (speed * deltaTime), character->GetPosition().y));
				}
					

				if ((character->GetCollisonBox().x - 0.000001f < mCollisionBoxes.at(i).x + mCollisionBoxes.at(i).width))
				{
					character->SetPosition(Vector2D((character->GetPosition().x + (speed * deltaTime)), character->GetPosition().y));
				}
					
				cout << "Just move" << endl;
				cout << "x: " << mCollisionBoxes.at(i).x;
				cout << " " << "y: " << mCollisionBoxes.at(i).y << endl;
				return true;
			}


 			if (character->IsJumping() && right)
			{
				character->SetPosition(Vector2D(character->GetPosition().x + (speed * deltaTime), character->GetPosition().y + (jump * deltaTime)));
				character->CancelJump();
				cout << "Jump and move" << endl;
				cout << "x: " << mCollisionBoxes.at(i).x;
				cout << " " << "y: " << mCollisionBoxes.at(i).y << endl;
				return true;
			}
			else if (character->IsJumping() && right)
			{
				character->SetPosition(Vector2D(character->GetPosition().x - (speed * deltaTime), character->GetPosition().y + (jump*deltaTime)));
				character->CancelJump();
				cout << "Jump and move" << endl;
				cout << "x: " << mCollisionBoxes.at(i).x;
				cout << " " << "y: " << mCollisionBoxes.at(i).y << endl;
				return true;
			}

			if (character->IsJumping() && !left)
			{
				character->SetPosition(Vector2D(character->GetPosition().x, character->GetPosition().y + (jump * deltaTime)));
				character->CancelJump();
				cout << "Just Jump" << endl;
				cout << "x: " << mCollisionBoxes.at(i).x;
				cout << " " << "y: " << mCollisionBoxes.at(i).y << endl;
				return true;
			}
			else if (character->IsJumping() && !right)
			{
				character->SetPosition(Vector2D(character->GetPosition().x, character->GetPosition().y + (jump * deltaTime)));
				character->CancelJump();
				cout << "Just Jump" << endl;
				cout << "x: " << mCollisionBoxes.at(i).x;
				cout << " " << "y: " << mCollisionBoxes.at(i).y << endl;
				return true;
			}

			
			cout << "Collision with " << i << " box at " << GetCollisionBox(i).x << " " << GetCollisionBox(i).y << endl << "Mario is at " << character->GetCollisonBox().x << " " << character->GetCollisonBox().y << endl;
			return true;
		}
	}
	return false;
}

Rect2D BlockCollider2::GetCollisionBox(int n)
{
	return Rect2D(mCollisionBoxes[n].x, mCollisionBoxes[n].y, mCollisionBoxes[n].width, mCollisionBoxes[n].height);
}

void BlockCollider2::LoadCollisions()
{

}
