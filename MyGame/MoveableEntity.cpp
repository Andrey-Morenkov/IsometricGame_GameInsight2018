#include "MoveableEntity.h"
#include "Settings.h"
#include "TextureWorker.h"

void MoveableEntity::render()
{
	TextureWorker::renderTextureRegion(mSelfTexture, mPosition, &mSelfTexture.getTextureTypes()[(int)mDirection]);
}

void MoveableEntity::setDirection(EntityDirection _direction)
{
	mDirection = _direction;
}

void MoveableEntity::setNewPath(AStar::CoordinateList _newPath)
{
	if (mPath.isCyclic())
	{
		return; //soon
	}

	mPath.clear();
	mPath.setRoute(_newPath);
}


EntityDirection MoveableEntity::getDirection()
{
	return mDirection;
}

PathWay& MoveableEntity::getPath()
{
	return mPath;
}

bool MoveableEntity::isNeedToMove()
{
	return (isNeedToExe() && !mPath.isFinished());
}

void MoveableEntity::setPositionFromTileIsoCoords(Coordinate2D _targetTileLeftTopCornerCoords)
{
	mPosition.setX(_targetTileLeftTopCornerCoords.getX() + (TILE_TEXTURE_WIDTH_IN_PIXELS / 2) - (mSelfTexture.getWidthEachTextureTypeInPixels() / 2));
	mPosition.setY(_targetTileLeftTopCornerCoords.getY() + (TILE_TEXTURE_HEIGHT_IN_PIXELS / 2) - mSelfTexture.getHeightEachTextureTypeInPixels());
}

Coordinate2D MoveableEntity::getTileISOCoordFromSelfPosition()
{
	return Coordinate2D(mPosition.getX() + (mSelfTexture.getWidthEachTextureTypeInPixels() / 2) - (TILE_TEXTURE_WIDTH_IN_PIXELS / 2), mPosition.getY() + mSelfTexture.getHeightEachTextureTypeInPixels() - (TILE_TEXTURE_HEIGHT_IN_PIXELS / 2));
}


