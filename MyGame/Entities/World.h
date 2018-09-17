#pragma once

#include "../Entity.h"
#include "../IsometricEngine.h"
#include "../Texture.h"


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
	Coordinate2D getTileISOCoordinates(Coordinate2D _incomingISOCoordinates);
	Coordinate2D getTileCoordinatesInWorld(Coordinate2D _incomingISOCoordinates);
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