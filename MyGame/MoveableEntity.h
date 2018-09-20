#pragma once
#include "Entity.h"
#include "PathWay.h"
#include "Interfaces/Runnable.h"

enum class EntityDirection
{
	UP_LEFT = 0,
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT,
	LEFT
};

class MoveableEntity : public Entity, public Runnable
{
protected:

	EntityDirection mDirection;
	PathWay         mPath;

	void loadTexture() override = 0;

public:

	MoveableEntity() {};
	virtual ~MoveableEntity() {};
	virtual void render();

	void setDirection(EntityDirection _direction);
	void setNewPath(AStar::CoordinateList _newPath);
	EntityDirection getDirection();
	PathWay& getPath();
	bool isNeedToMove();

	virtual void setPositionFromTileIsoCoords(Coordinate2D _targetTileLeftTopCornerCoords);
	virtual Coordinate2D getTileISOCoordFromSelfPosition();
	virtual Coordinate2D getProjectionToTileISOcoord() = 0;
};