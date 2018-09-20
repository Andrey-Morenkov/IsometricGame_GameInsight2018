#pragma once
#include "../MoveableEntity.h"
#include "../Entities/Cannon.h"

class Fireball : public MoveableEntity
{
private:

	void loadTexture() override;
	

public:

	Fireball();
	Fireball(Coordinate2D _startCoord);
	virtual ~Fireball();

	void render() override;

	void setPositionFromTileIsoCoords(Coordinate2D _targetTileLeftTopCornerCoords) override;
	Coordinate2D getTileISOCoordFromSelfPosition() override;
	Coordinate2D getProjectionToTileISOcoord() override;
	//void setDirectionFromFiredCannon(Cannon* _owner);
};

