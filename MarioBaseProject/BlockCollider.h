#pragma once
#include "Commons.h"
#include "LevelMap.h"
#include "Texture2D.h"
#include "Character.h"
#include "Collisions.h"
#include <vector>

class BlockCollider
{
public:
	BlockCollider(LevelMap* map, SDL_Renderer* renderer);
	~BlockCollider();
	bool CheckCollision(Character* character);
	Rect2D GetCollisionBox(int n);
	void LoadCollisions();
	void UpdateCollisions(LevelMap* map);
	

private:
	Vector2D mPosition;
	LevelMap* mLevelMap;
	Character* myCharacter;
	vector<Rect2D> mCollisionBoxes;
	Rect2D* mCollisionBox;
	SDL_Rect* mRectToDraw;
	vector<Character*> testChars;
	Character* testChar;
	int numBox;
};

