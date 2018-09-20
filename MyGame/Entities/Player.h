#pragma once
#include "../MoveableEntity.h"

class Player : public MoveableEntity
{
private:

	void loadTexture() override;

public:

	Player();
	Player(Coordinate2D _startCoord);
	virtual ~Player();

	Coordinate2D getProjectionToTileISOcoord() override;
	void setPositionISOcoordFromProjectionCoord(Coordinate2D _proj);
};



