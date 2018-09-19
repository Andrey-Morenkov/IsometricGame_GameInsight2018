#pragma once
#include "Entity.h"
#include "PathWay.h"

enum class EntityDirection
{
	UP_LEFT = 0,
	UP,
	UP_RIGHT,
	RIGHT,
	RIGHT_DOWN,
	DOWN,
	DOWN_LEFT,
	LEFT
};

class MoveableEntity : public Entity
{
protected:
	EntityDirection mDirection;
	int             mSpeed;					//pixels per tick
	PathWay         mPath;

public:
	MoveableEntity() {};
	virtual ~MoveableEntity() {};

	void render() override = 0;

	void setDirection(EntityDirection _direction);
	void setPostition(Coordinate2D _newPos);
	void setSpeed(int _speed);
	Coordinate2D getPosition();
	EntityDirection getDirection();
	int getSpeed();
	void setNewPath(AStar::CoordinateList _newPath);

	PathWay getPath();
};