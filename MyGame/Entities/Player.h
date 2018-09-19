#pragma once
#include "../MoveableEntity.h"
#include "../Texture.h"

class Player : public MoveableEntity
{
private:

	Texture mPlayerTexture;
	
public:
	Player();
	Player(Coordinate2D _startCoord);
	virtual ~Player();

	void setPositionFromTileIsoCoords(Coordinate2D _targetTileLeftTopCornerCoords);
	Coordinate2D getTileISOCoordFromSelfPosition();
	Coordinate2D getProjectionToTileISOcoord();

	void render() override;
};



