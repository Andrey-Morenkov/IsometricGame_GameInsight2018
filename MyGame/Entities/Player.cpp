#include "Player.h"
#include "../Settings.h"
#include "../TextureWorker.h"

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

void Player::setPositionFromTileIsoCoords(Coordinate2D _targetTileLeftTopCornerCoords)
{
	mPosition.setX(_targetTileLeftTopCornerCoords.getX() + (TILE_TEXTURE_WIDTH_IN_PIXELS / 2) - (PLAYER_TEXTURE_WIDTH_IN_PIXELS / 2));
	mPosition.setY(_targetTileLeftTopCornerCoords.getY() + (TILE_TEXTURE_HEIGHT_IN_PIXELS / 2) - PLAYER_TEXTURE_HEIGHT_IN_PIXELS);
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

Coordinate2D Player::getDownCenterPosition()
{
	return Coordinate2D(mPosition.getX() + (PLAYER_TEXTURE_WIDTH_IN_PIXELS / 2), mPosition.getY() + PLAYER_TEXTURE_HEIGHT_IN_PIXELS);
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
