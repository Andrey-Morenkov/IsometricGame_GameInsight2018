#pragma once
#include "../MoveableEntity.h"

class NPC :	public MoveableEntity
{
private:

	void loadTexture() override;

public:

	NPC();
	NPC(Coordinate2D _startCoord);
	virtual ~NPC();

	Coordinate2D getProjectionToTileISOcoord() override;
};

