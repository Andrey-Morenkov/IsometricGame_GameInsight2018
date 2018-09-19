#pragma once

#include "../Entity.h"
#include "../IsometricEngine.h"
#include "../Texture.h"
#include "../Settings.h"


class World : public Entity
{
private:

	unsigned int mWidthTiles;
	unsigned int mHeightTiles;
	Texture      mTextureTiles;
	Texture      mTextureWalls;

	void renderFloor();
	void renderStartFinishTiles();
	void renderWalls();

public:
	
	World();
	World(unsigned int _widthTiles, unsigned int _heightTiles);
	virtual ~World();

	void render() override;

	void setStartingPoint(Coordinate2D _startingPoint);
	Coordinate2D getStartingPoint();
	Coordinate2D& getStartingPointLink();
	Coordinate2D getTileISOCoordinatesFromISOCoords(Coordinate2D _incomingISOCoordinates); // returns upper left corner coord of local tile
	Coordinate2D getTileISOCoordinatesFromMapCoords(Coordinate2D _incomintMapCoordinates); // returns upper left corner coord of local tile
	Coordinate2D getTileMapCoordinatesFromISOCoords(Coordinate2D _incomingISOCoordinates); // returns tile number ,(0,0) for example
	Coordinate2D getTileISOProjectionFromSelfISOCoords(Coordinate2D _incomingISOCoordinates); // returns center of tile from left upper corner
};

enum class TileType
{
	DEFAULT = 0,
	START,
	FINISH
};

enum class WallType
{
	LEFT = 0,
	RIGHT
};

#define MAP_LEFT_DOWN_CORNER Coordinate2D(0, MAP_WIDTH_TILES - 1)
#define MAP_RIGHT_UP_CORNER Coordinate2D(MAP_HEIGHT_TILES - 1, 0)
#define MAP_START_POINT MAP_LEFT_DOWN_CORNER
#define MAP_FINISH_POINT MAP_RIGHT_UP_CORNER