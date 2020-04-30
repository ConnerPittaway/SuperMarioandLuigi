#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"


Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map)
{
	mMovingLeft = false;
	mMovingRight = false;
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mPosition = startPosition;
	mFacingDirection = FACING_RIGHT;
	mCollisionRadius = 7.5f;
	mCurrentLevelMap = map;
	if (!mTexture->LoadFromFile(imagePath))
	{
		cout << "Failed to load character texture" << endl;
	}
}


Character::~Character()
{
	mRenderer = nullptr;
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

FACING Character::GetDirection()
{
	return mFacingDirection;
}

void Character::SetDirection(FACING dir)
{
	mFacingDirection = dir;
}

void Character::SetMovingLeft(bool left)
{
	mMovingLeft = left;
}

void Character::SetMovingRight(bool right)
{
	mMovingRight = right;
}

bool Character::GetMovingLeft()
{
	return mMovingLeft;
}

bool Character::GetMovingRight()
{
	return mMovingRight;
}

float Character::GetMovementSpeed()
{
	return mMovementSpeed;
}

void Character::SetMovementSpeed()
{
	mMovementSpeed = 0.0f;
}

void Character::Render(Camera* cam)
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(cam, mPosition, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(cam,mPosition, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

void Character::AddGravity(float deltaTime)
{
		mPosition.y += deltaTime * GRAVITY;
		mCanJump = false;
}

void Character::Update(float deltaTime, SDL_Event e, float speed)
{
	if (mMovingLeft)
	{
		MoveLeft(deltaTime, speed);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime, speed);
	}
}

void Character::MoveLeft(float deltaTime, float speed)
{
	mFacingDirection = FACING_LEFT;
	SetPosition(Vector2D(mPosition.x -= speed*deltaTime, mPosition.y));
}

void Character::MoveRight(float deltaTime, float speed)
{
	mFacingDirection = FACING_RIGHT;
	SetPosition(Vector2D(mPosition.x += speed*deltaTime, mPosition.y));
}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

Rect2D Character::GetCollisonBox()
{
 return Rect2D(mPosition.x, mPosition.y - 1, mTexture->GetWidth()/4, mTexture->GetHeight()/2);
}

bool Character::IsJumping()
{
	return mJumping;
}

void Character::CancelJump()
{
	mJumpForce = 0;
	mJumping = false;
}

float Character::GetJumpForce()
{
	return mJumpForce;
}

void Character::SetAlive(bool alive)
{
	mAlive = alive;
}

bool Character::GetAlive()
{
	return mAlive;
}

void Character::SetInjured(bool injured)
{
	mInjured = injured;
}

bool Character::GetInjured()
{
	return mInjured;
}

