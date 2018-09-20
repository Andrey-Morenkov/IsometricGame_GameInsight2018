#include "Entity.h"

Entity::Entity()
{
	mPosition.setX(0);
	mPosition.setY(0);
}

Entity::Entity(Coordinate2D _startCoord)
{
	mPosition = _startCoord;
}


Entity::~Entity()
{
}

Coordinate2D Entity::getPosition()
{
	return mPosition;
}

void Entity::setPosition(Coordinate2D _newPosition)
{
	mPosition = _newPosition;
}
