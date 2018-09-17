#pragma once

#include "Entity.h"
#include "IsometricEngine.h"
#include "Texture.h"


class World : public Entity
{
private:

	unsigned int mWidthTiles;
	unsigned int mHeightTiles;
	Texture      mTextureTiles;
	Texture      mTextureWalls;

	void renderFloor();
	void renderWalls();

public:
	
	World();
	World(unsigned int _widthTiles, unsigned int _heightTiles);
	virtual ~World();

	void render() override;

	void setStartingPoint(Coordinate2D _startingPoint);
	Coordinate2D getStartingPoint();
	void getTileCoordinates(Coordinate2D & _incomingCoordinates, Coordinate2D & _tileCoordinates);
};

enum class TileType
{
	DEFAULT = 0
};

enum class WallType
{
	LEFT = 0,
	RIGHT
};