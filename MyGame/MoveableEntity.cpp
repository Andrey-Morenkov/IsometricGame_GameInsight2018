#include "MoveableEntity.h"

void MoveableEntity::setDirection(EntityDirection _direction)
{
	mDirection = _direction;
}

void MoveableEntity::setPostition(Coordinate2D _newPos)
{
	mPosition = _newPos;
}

void MoveableEntity::setSpeed(int _speed)
{
	mSpeed = _speed;
}

Coordinate2D MoveableEntity::getPosition()
{
	return mPosition;
}

EntityDirection MoveableEntity::getDirection()
{
	return mDirection;
}

int MoveableEntity::getSpeed()
{
	return mSpeed;
}

void MoveableEntity::setNewPath(AStar::CoordinateList _newPath)
{
	mPath.clear();
	mPath.setRoute(_newPath);
}

PathWay MoveableEntity::getPath()
{
	return mPath;
}
