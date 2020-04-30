#pragma once
#include "Commons.h"
#include "LevelLoader.h"
#include "Texture2D.h"
#include "Character.h"
#include "Collisions.h"
#include <vector>

class BlockCollider2
{
public:
	BlockCollider2(LevelLoader* map, SDL_Renderer* renderer);
	~BlockCollider2();
	bool CheckCollision(Character* character, bool right, bool left, float deltaTime, float speed, float jump);
	Rect2D GetCollisionBox(int n);
	void LoadCollisions();
	void UpdateCollisions(LevelLoader* map);


private:
	Vector2D mPosition;
	LevelLoader *LevMap;
	Character* myCharacter;
	vector<Rect2D> mCollisionBoxes;
	Rect2D* mCollisionBox;
	SDL_Rect* mRectToDraw;
	vector<Character*> testChars;
	Character* testChar;
	int numBox;
};

