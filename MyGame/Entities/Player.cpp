#include "Player.h"
#include "../Settings.h"
#include "../TextureWorker.h"

void Player::loadTexture()
{
	mSelfTexture.setWidthEachTextureTypeInPixels(PLAYER_TEXTURE_WIDTH_IN_PIXELS);
	mSelfTexture.setHeightEachTextureTypeInPixels(PLAYER_TEXTURE_HEIGHT_IN_PIXELS);
	mSelfTexture.loadFromPath(PLAYER_TEXTURE_PATH);
}

Player::Player()
{
	mDirection = EntityDirection::UP_LEFT; //default
	loadTexture();
	mTimeExeInSec = PLAYER_SPEED;
	mPath.setCyclicMode(false);
}

Player::Player(Coordinate2D _startCoord) : Player()
{
	mPosition = _startCoord;
}

Player::~Player()
{
}

Coordinate2D Player::getProjectionToTileISOcoord()
{
	return Coordinate2D(mPosition.getX() + (PLAYER_TEXTURE_WIDTH_IN_PIXELS / 2), mPosition.getY() + PLAYER_TEXTURE_HEIGHT_IN_PIXELS);
}

void Player::setPositionISOcoordFromProjectionCoord(Coordinate2D _proj)
{
	mPosition.setX(_proj.getX() - mSelfTexture.getWidthEachTextureTypeInPixels() / 2);
	mPosition.setY(_proj.getY() - mSelfTexture.getHeightEachTextureTypeInPixels());
}
