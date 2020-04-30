#include "BlockCollider3.h"

BlockCollider3::BlockCollider3(LevelLoader* map, SDL_Renderer* renderer)
{
	for (unsigned int y = 1; y < map->GetColumnSize(); y++)
	{
		for (unsigned int x = 0; x < map->GetRowSize(); x++)
		{
			if (map->GetTileAt(y, x) == 'p')
			{
				mCollisionBox = &Rect2D((x) * 16, (y - 1) * 16, 16, 16);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << "x: " << mCollisionBox->x;
				cout << " " << "y: " << mCollisionBox->y << endl;
			}
			else if (map->GetTileAt(y, x) == 'b')
			{
				mCollisionBox = &Rect2D((x) * 16, (y - 1) * 16, 16, 16);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << "x: " << mCollisionBox->x;
				cout << " " << "y: " << mCollisionBox->y << endl;
			}
			else if (map->GetTileAt(y, x) == 'y')
			{
				mCollisionBox = &Rect2D((x) * 16, (y - 1) * 16, 16, 16);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << "x: " << mCollisionBox->x;
				cout << " " << "y: " << mCollisionBox->y << endl;
			}
			else if (map->GetTileAt(y, x) == 'z')
			{
				mCollisionBox = &Rect2D((x) * 16, (y - 1) * 16, 16, 16);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << "x: " << mCollisionBox->x;
				cout << " " << "y: " << mCollisionBox->y << endl;
			}
			else if (map->GetTileAt(y, x) == 'w')
			{
				mCollisionBox = &Rect2D((x) * 16, (y - 1) * 16, 16, 16);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << "x: " << mCollisionBox->x;
				cout << " " << "y: " << mCollisionBox->y << endl;
			}
			else if (map->GetTileAt(y, x) == 'x')
			{
				mCollisionBox = &Rect2D((x) * 16, (y - 1) * 16, 16, 16);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << "x: " << mCollisionBox->x;
				cout << " " << "y: " << mCollisionBox->y << endl;
			}
			else if (map->GetTileAt(y, x) == 's')
			{
				mCollisionBox = &Rect2D((x) * 16, (y - 1) * 16, 16, 16);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << "x: " << mCollisionBox->x;
				cout << " " << "y: " << mCollisionBox->y << endl;
				cout << mCollisionBox->width << endl;
				cout << mCollisionBox->height << endl;
			}
			else if (map->GetTileAt(y, x) == 'o')
			{
				mCollisionBox = &Rect2D((x) * 16, (y - 1) * 16, 16, 16);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << "x: " << mCollisionBox->x;
				cout << " " << "y: " << mCollisionBox->y << endl;
				cout << mCollisionBox->width << endl;
				cout << mCollisionBox->height << endl;
			}
			else if (map->GetTileAt(y, x) == 'j')
			{
				mCollisionBox = &Rect2D((x) * 16, (y - 1) * 16, 16, 16);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << "x: " << mCollisionBox->x;
				cout << " " << "y: " << mCollisionBox->y << endl;
				cout << mCollisionBox->width << endl;
				cout << mCollisionBox->height << endl;
			}
			else if (map->GetTileAt(y, x) == 'l')
			{
				mCollisionBox = &Rect2D((x) * 16, (y - 1) * 16, 16, 16);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << "x: " << mCollisionBox->x;
				cout << " " << "y: " << mCollisionBox->y << endl;
				cout << mCollisionBox->width << endl;
				cout << mCollisionBox->height << endl;
			}
			else if (map->GetTileAt(y, x) == 'i')
			{
				mCollisionBox = &Rect2D((x) * 16, (y - 1) * 16, 16, 16);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << "x: " << mCollisionBox->x;
				cout << " " << "y: " << mCollisionBox->y << endl;
				cout << mCollisionBox->width << endl;
				cout << mCollisionBox->height << endl;
			}
			else
			{

			}
		}
	}
}

BlockCollider3::~BlockCollider3()
{
	LevMap = NULL;
}

void BlockCollider3::UpdateCollisions(LevelLoader* map)
{
	mCollisionBoxes.clear();
	for (unsigned int y = 1; y < map->GetColumnSize(); y++)
	{
		for (unsigned int x = 0; x < map->GetRowSize(); x++)
		{
			if (map->GetTileAt(y, x) == '1')
			{
				mCollisionBox = &Rect2D(x * 16, (y - 1) * 16, 16, 16);
				mCollisionBoxes.push_back(*mCollisionBox);

				cout << "x: " << mCollisionBox->x;
				cout << " " << "y: " << mCollisionBox->y << endl;
				cout << mCollisionBox->width << endl;
				cout << mCollisionBox->height << endl;
			}
		}
	}
}

bool BlockCollider3::CheckCollision(Character* character, bool right, bool left, float deltaTime, float speed, float jump)
{
	for (int i = 0; i < mCollisionBoxes.size(); i++)
	{
		if (Collisions::Instance()->Box(character->GetCollisonBox(), mCollisionBoxes.at(i)))
		{
			if (!character->IsJumping() && left)
			{
				if ((character->GetCollisonBox().x > (mCollisionBoxes.at(i).x + (mCollisionBoxes.at(i).width/2))))
				{
					character->CancelJump();
					character->SetPosition(Vector2D(character->GetPosition().x + (speed * deltaTime), character->GetPosition().y));
					cout << "Right Side" << endl;
					return true;
				}

				cout << "Just move" << endl;
				cout << "x: " << mCollisionBoxes.at(i).x;
				cout << " " << "y: " << mCollisionBoxes.at(i).y << endl;
				return true;
			}
			else if (!character->IsJumping() && right)
			{
				if ((character->GetCollisonBox().x + character->GetCollisonBox().width) + 0.0001f < (mCollisionBoxes.at(i).x + (mCollisionBoxes.at(i).width / 2)))
				{
					character->CancelJump();
					character->SetPosition(Vector2D(character->GetPosition().x - (speed * deltaTime), character->GetPosition().y));

					cout << "Moving right, left  side" << endl;
					return true;
				}


				//if ((character->GetCollisonBox().x - 0.000001f) < (mCollisionBoxes.at(i).x + mCollisionBoxes.at(i).width)/2)
				//{
				//	character->SetPosition(Vector2D((character->GetPosition().x + (speed * deltaTime)), character->GetPosition().y));
				//}

				cout << "Right move" << endl;
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

bool BlockCollider3::CheckKoopaCollision(CharacterKoopa* koopa, bool right, bool left)
{
	for (int i = 0; i < mCollisionBoxes.size(); i++)
	{
		if (Collisions::Instance()->Box(koopa->GetKoopaCollisionBox(), mCollisionBoxes.at(i)))
		{
			if (!koopa->IsJumping() && left)
			{
				if ((koopa->GetKoopaCollisionBox().x > (mCollisionBoxes.at(i).x + (mCollisionBoxes.at(i).width / 2))))
				{
					koopa->CancelJump();
					koopa->SetMovingLeft(false);
					koopa->SetDirection(FACING_RIGHT);
					cout << "Right Side" << endl;
					return true;
				}

				cout << "Just move" << endl;
				cout << "x: " << mCollisionBoxes.at(i).x;
				cout << " " << "y: " << mCollisionBoxes.at(i).y << endl;
				return true;
			}
			else if (!koopa->IsJumping() && right)
			{
				if ((koopa->GetKoopaCollisionBox().x + koopa->GetKoopaCollisionBox().width) + 0.0001f < (mCollisionBoxes.at(i).x + (mCollisionBoxes.at(i).width / 2)))
				{
					koopa->CancelJump();
					koopa->SetMovingRight(false);
					koopa->SetDirection(FACING_LEFT);
					cout << "Moving right, left  side" << endl;
					return true;
				}
			}
		}
	}
}

Rect2D BlockCollider3::GetCollisionBox(int n)
{
	return Rect2D(mCollisionBoxes[n].x, mCollisionBoxes[n].y, mCollisionBoxes[n].width, mCollisionBoxes[n].height);
}

void BlockCollider3::LoadCollisions()
{

}
