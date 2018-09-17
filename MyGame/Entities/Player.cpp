#include "Player.h"
#include "Settings.h"
#include "TextureWorker.h"

Player::Player()
{
	mPosition.setX(0);
	mPosition.setY(0);
	mDirection = PlayerDirection::UP_RIGHT;
	mPlayerTexture.setWidthEachTextureTypeInPixels(PLAYER_TEXTURE_WIDTH_IN_PIXELS);
	mPlayerTexture.setHeightEachTextureTypeInPixels(PLAYER_TEXTURE_HEIGHT_IN_PIXELS);
	mPlayerTexture.loadFromPath(PLAYER_TEXTURE_PATH);
	mSpeed = 1;
	mIsMoving = false;
}

Player::Player(Coordinate2D _startCoord) : Player()
{
	mPosition = _startCoord;
}


Player::~Player()
{
}

void Player::render()
{
	TextureWorker::renderTextureRegion(mPlayerTexture, mPosition, &mPlayerTexture.getTextureTypes()[(int)mDirection]);
}

void Player::setDirection(PlayerDirection _direction)
{
	mDirection = _direction;
}

void Player::setPostition(Coordinate2D _newPos)
{
	mPosition = _newPos;
}

void Player::setSpeed(int _speed)
{
	mSpeed = _speed;
}

void Player::setIsMoving(bool _ismoving)
{
	mIsMoving = _ismoving;
}

Coordinate2D Player::getPosition()
{
	return mPosition;
}

PlayerDirection Player::getDirection()
{
	return mDirection;
}

int Player::getSpeed()
{
	return mSpeed;
}

bool Player::getIsMoving()
{
	return mIsMoving;
}
