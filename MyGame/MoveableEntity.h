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
	double          mTimeForStepInSec;
	PathWay         mPath;

public:
	MoveableEntity() { mLastUpdatedTick = 0; };
	virtual ~MoveableEntity() {};

	void render() override = 0;

	void setDirection(EntityDirection _direction);
	void setPostition(Coordinate2D _newPos);
	void setTimeForStepInSec(double _sec);
	Coordinate2D getPosition();
	EntityDirection getDirection();
	double getTimeForStepInSec();
	void setNewPath(AStar::CoordinateList _newPath);

	PathWay& getPath();
	unsigned int mLastUpdatedTick;
};