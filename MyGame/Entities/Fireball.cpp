#include "Fireball.h"
#include "../Settings.h"
#include "../TextureWorker.h"

void Fireball::loadTexture()
{
	mSelfTexture.setWidthEachTextureTypeInPixels(FIREBALL_TEXTURE_WIDTH_IN_PIXELS);
	mSelfTexture.setHeightEachTextureTypeInPixels(FIREBALL_TEXTURE_HEIGHT_IN_PIXELS);
	mSelfTexture.loadFromPath(FIREBALL_TEXTURE_PATH);
}

Fireball::Fireball()
{
	//mDirection = EntityDirection::UP_LEFT;
	loadTexture();
	mTimeExeInSec = FIREBALL_SPEED;
	mPath.setCyclicMode(false);
}

Fireball::Fireball(Coordinate2D _startCoord) : Fireball()
{
	mPosition = _startCoord;
}


Fireball::~Fireball()
{
}

void Fireball::render()
{
	TextureWorker::renderTextureRegion(mSelfTexture, mPosition, &mSelfTexture.getTextureTypes()[0]);
}

void Fireball::setPositionFromTileIsoCoords(Coordinate2D _targetTileLeftTopCornerCoords)
{
	mPosition.setX(_targetTileLeftTopCornerCoords.getX());
	mPosition.setY(_targetTileLeftTopCornerCoords.getY() + (TILE_TEXTURE_HEIGHT_IN_PIXELS / 2) - WALL_TEXTURE_HEIGHT_IN_PIXELS); //yes, wall is true     
}

Coordinate2D Fireball::getTileISOCoordFromSelfPosition()
{
	return Coordinate2D(mPosition.getX(), mPosition.getY() + WALL_TEXTURE_HEIGHT_IN_PIXELS - (TILE_TEXTURE_HEIGHT_IN_PIXELS / 2));
}

Coordinate2D Fireball::getProjectionToTileISOcoord()
{
	return Coordinate2D(mPosition.getX() + (FIREBALL_TEXTURE_WIDTH_IN_PIXELS / 2), mPosition.getY() + WALL_TEXTURE_HEIGHT_IN_PIXELS); //yes, wall is true
}

/*
void Fireball::setDirectionFromFiredCannon(Cannon* _owner)
{
	switch (_owner->getType())
	{
		case WallType::RIGHT:
		{
			mDirection = EntityDirection::DOWN_LEFT;
			break;
		}
		case WallType::LEFT:
		{
			mDirection = EntityDirection::DOWN_RIGHT;
			break;
		}
	}
}*/
