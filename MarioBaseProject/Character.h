#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "LevelMap.h"
#include "Camera.h"

class Texture2D;

class Character
{
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render(Camera* cam);
	virtual void Update(float deltaTime, SDL_Event e, float speed);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();
	
	virtual Rect2D GetCollisonBox();

	void AddGravity(float deltaTime);

	void Jump();

	bool IsJumping();
	void CancelJump();
	float GetJumpForce();

	void SetAlive(bool alive);
	bool GetAlive();
	
	void SetInjured(bool injured);
	bool GetInjured();

	FACING GetDirection();
	void SetDirection(FACING dir);

	void SetMovingLeft(bool left);
	void SetMovingRight(bool right);
	bool GetMovingLeft();
	bool GetMovingRight();

	float GetMovementSpeed();
	void SetMovementSpeed();

protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	virtual void MoveLeft(float deltaTime, float speed);
	virtual void MoveRight(float deltaTime, float speed);
	float mCollisionRadius;
	bool mJumping;
	bool mCanJump;
	float mJumpForce;
	bool mAlive = true;
	bool mInjured = false;
	float mMovementSpeed;
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;

private:


	LevelMap* mCurrentLevelMap;
};

