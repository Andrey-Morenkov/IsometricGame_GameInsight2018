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
	Coordinate2D getRightWallStartISOCoord();
	Coordinate2D getLeftWallStartISOCoord();

	void loadTexture() override;
	Coordinate2D getTileOnSpecificPositionISOCoord(Coordinate2D _position);

public:
	
	World();
	World(unsigned int _widthTiles, unsigned int _heightTiles);
	virtual ~World();

	void render() override;

	Coordinate2D getRightWallTileOnSpecificPositionIsoCoord(int _position);
	Coordinate2D getLeftWallTileOnSpecificPositionIsoCoord(int _position);
	int getRightWallTileMapCoordbyIsoCoord(Coordinate2D _position);
	int getLeftWallTileMapCoordbyIsoCoord(Coordinate2D _position);

	void setStartingPoint(Coordinate2D _startingPoint);
	Coordinate2D getStartingPoint();
	
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