#include "Player.h"
#include "../Settings.h"
#include "../TextureWorker.h"

Player::Player()
{
	mPosition.setX(0);
	mPosition.setY(0);
	mDirection = EntityDirection::UP_RIGHT;
	mPlayerTexture.setWidthEachTextureTypeInPixels(PLAYER_TEXTURE_WIDTH_IN_PIXELS);
	mPlayerTexture.setHeightEachTextureTypeInPixels(PLAYER_TEXTURE_HEIGHT_IN_PIXELS);
	mPlayerTexture.loadFromPath(PLAYER_TEXTURE_PATH);
	mTimeForStepInSec = 0.5;
	mPath.setCyclicMode(false);
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

void Player::setPositionFromTileIsoCoords(Coordinate2D _targetTileLeftTopCornerCoords)
{
	mPosition.setX(_targetTileLeftTopCornerCoords.getX() + (TILE_TEXTURE_WIDTH_IN_PIXELS / 2) - (PLAYER_TEXTURE_WIDTH_IN_PIXELS / 2));
	mPosition.setY(_targetTileLeftTopCornerCoords.getY() + (TILE_TEXTURE_HEIGHT_IN_PIXELS / 2) - PLAYER_TEXTURE_HEIGHT_IN_PIXELS);
}

Coordinate2D Player::getTileISOCoordFromSelfPosition()
{
	return Coordinate2D(mPosition.getX() + PLAYER_TEXTURE_WIDTH_IN_PIXELS/2 - TILE_TEXTURE_WIDTH_IN_PIXELS/2, mPosition.getY() + PLAYER_TEXTURE_HEIGHT_IN_PIXELS - TILE_TEXTURE_HEIGHT_IN_PIXELS/2);
}

Coordinate2D Player::getProjectionToTileISOcoord()
{
	return Coordinate2D(mPosition.getX() + (PLAYER_TEXTURE_WIDTH_IN_PIXELS / 2), mPosition.getY() + PLAYER_TEXTURE_HEIGHT_IN_PIXELS);
}
