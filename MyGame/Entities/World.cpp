#include "World.h"
#include "../Settings.h"
#include "../Core.h"
#include "../SupportMacroses.h"
#include "../TextureWorker.h"

World::World()
{
	mWidthTiles = 0;
	mHeightTiles = 0;
	loadTexture();
}

void World::loadTexture()
{
	mTextureTiles.setWidthEachTextureTypeInPixels(TILE_TEXTURE_WIDTH_IN_PIXELS);
	mTextureTiles.setHeightEachTextureTypeInPixels(TILE_TEXTURE_HEIGHT_IN_PIXELS);
	mTextureTiles.loadFromPath(TILE_TEXTURE_PATH);

	mTextureWalls.setWidthEachTextureTypeInPixels(WALL_TEXTURE_WIDTH_IN_PIXELS);
	mTextureWalls.setHeightEachTextureTypeInPixels(WALL_TEXTURE_HEIGHT_IN_PIXELS);
	mTextureWalls.loadFromPath(WALL_TEXTURE_PATH);
}

World::World(unsigned int _widthTiles, unsigned int _heightTiles) : World()
{
	mWidthTiles = _widthTiles;
	mHeightTiles = _heightTiles;
}

World::~World()
{
}

void World::setStartingPoint(Coordinate2D _startingPoint)
{
	mPosition = _startingPoint;
}

Coordinate2D World::getStartingPoint()
{
	return mPosition;
}

Coordinate2D World::getTileISOCoordinatesFromISOCoords(Coordinate2D _incomingISOCoordinates)
{
	return getTileISOCoordinatesFromMapCoords(getTileMapCoordinatesFromISOCoords(_incomingISOCoordinates));	
}

Coordinate2D World::getTileISOCoordinatesFromMapCoords(Coordinate2D _incomintMapCoordinates)
{
	Coordinate2D res;
	if ((_incomintMapCoordinates.getX() < 0) || (_incomintMapCoordinates.getY() < 0))
	{
		return Coordinate2D(-1, -1);
	}

	return getTileOnSpecificPositionISOCoord(_incomintMapCoordinates);
}

Coordinate2D World::getTileMapCoordinatesFromISOCoords(Coordinate2D _incomingISOCoordinates)
{
	double isoLeftLineCoeff = -0.5;
	double isoRightLineCoeff = 0.5;
	int lineStepX = TILE_SIZE_IN_PIXELS;
	int lineStepY = TILE_SIZE_IN_PIXELS - 1;

	Coordinate2D pureIncomingCoordinates;
	pureIncomingCoordinates.setX(_incomingISOCoordinates.getX() - (mPosition.getX() + (mTextureTiles.getWidthEachTextureTypeInPixels() / 2)));
	pureIncomingCoordinates.setY(_incomingISOCoordinates.getY() - mPosition.getY());
	//LOG_INFO("Pure coordinates (%d,%d)", pureIncomingCoordinates.getX(), pureIncomingCoordinates.getY());

	if (pureIncomingCoordinates.getY() < 0)
	{
		return Coordinate2D(-1, -1);
	}

	//LOG_INFO("Pure coordinates (%d,%d)", pureIncomingCoordinates.getX(), pureIncomingCoordinates.getY());

	int row = (pureIncomingCoordinates.getY() - (isoLeftLineCoeff * (double)pureIncomingCoordinates.getX())) / lineStepX;
	int column = (pureIncomingCoordinates.getY() - (isoRightLineCoeff * (double)pureIncomingCoordinates.getX())) / lineStepY;

	return Coordinate2D(row, column);
}

Coordinate2D World::getTileISOProjectionFromSelfISOCoords(Coordinate2D _incomingISOCoordinates)
{
	return Coordinate2D(_incomingISOCoordinates.getX() + mTextureTiles.getWidthEachTextureTypeInPixels()/2, _incomingISOCoordinates.getY() + mTextureTiles.getHeightEachTextureTypeInPixels()/2);
}

void World::renderFloor()
{
	Coordinate2D currentPoint;
	Coordinate2D floorBegin = getStartingPoint();
	IsometricEngine::convertIsometricTo2D(floorBegin);

	//LOG_INFO("Render floor. Starting point = (%d,%d), floor begin 2D = (%d,%d)", mStartingPoint.getX(), mStartingPoint.getY(), floorBegin.getX(), floorBegin.getY());

	for (int i = 0; i < mWidthTiles; i++)
	{
		for (int j = 0; j < mHeightTiles; j++)
		{
			currentPoint.setX(floorBegin.getX() + i * ((double)mTextureTiles.getWidthEachTextureTypeInPixels() / 2.0));
			currentPoint.setY(floorBegin.getY() + j * (mTextureTiles.getHeightEachTextureTypeInPixels()));

			//LOG_INFO("Render floor. i = %d, j = %d, current point = (%d, %d)", i, j, currentPoint.getX(), currentPoint.getY());
			IsometricEngine::convert2DtoIsometric(currentPoint);
			//LOG_INFO("Render floor. Isometric point = (%d,%d)", currentPoint.getX(), currentPoint.getY());
			TextureWorker::renderTextureRegion(mTextureTiles, currentPoint, &mTextureTiles.getTextureTypes()[(int)TileType::DEFAULT]);
		}
	}
	/*
	for (int i = 0; i < mWidthTiles; i++)
	{
		for (int j = 0; j < mHeightTiles; j++)
		{
			TextureWorker::renderTextureRegion(mTextureTiles, getTileOnSpecificPositionISOCoord(Coordinate2D(i,j)), &mTextureTiles.getTextureTypes()[(int)TileType::DEFAULT]);
		}
	}*/

}

void World::renderStartFinishTiles()
{
	TextureWorker::renderTextureRegion(mTextureTiles, getTileISOCoordinatesFromMapCoords(MAP_START_POINT), &mTextureTiles.getTextureTypes()[(int)TileType::START]);
	TextureWorker::renderTextureRegion(mTextureTiles, getTileISOCoordinatesFromMapCoords(MAP_FINISH_POINT), &mTextureTiles.getTextureTypes()[(int)TileType::FINISH]);
}

void World::renderWalls()
{
	Coordinate2D currentPoint;
	Coordinate2D wallsBeginRight = getStartingPoint();
	Coordinate2D wallsBeginLeft;

	wallsBeginRight.setX(wallsBeginRight.getX() + 0.5 * mTextureTiles.getWidthEachTextureTypeInPixels());
	wallsBeginRight.setY(wallsBeginRight.getY() - (mTextureWalls.getHeightEachTextureTypeInPixels() - 0.5 * mTextureTiles.getHeightEachTextureTypeInPixels()));

	wallsBeginLeft = wallsBeginRight;
	wallsBeginLeft.setX(wallsBeginLeft.getX() - mTextureWalls.getWidthEachTextureTypeInPixels());
	IsometricEngine::convertIsometricTo2D(wallsBeginLeft);
	IsometricEngine::convertIsometricTo2D(wallsBeginRight);

	for (int i = 0; i < mWidthTiles; i++)
	{
		currentPoint.setX(wallsBeginRight.getX() + i * mTextureWalls.getWidthEachTextureTypeInPixels());
		currentPoint.setY(wallsBeginRight.getY());
		IsometricEngine::convert2DtoIsometric(currentPoint);
		TextureWorker::renderTextureRegion(mTextureWalls, currentPoint, &mTextureWalls.getTextureTypes()[(int)WallType::RIGHT]);
	}

	for (int j = 0; j < mHeightTiles - 1; j++)
	{
		currentPoint.setX(wallsBeginLeft.getX());
		currentPoint.setY(wallsBeginLeft.getY() + j * (mTextureWalls.getWidthEachTextureTypeInPixels()));
		IsometricEngine::convert2DtoIsometric(currentPoint);
		TextureWorker::renderTextureRegion(mTextureWalls, currentPoint, &mTextureWalls.getTextureTypes()[(int)WallType::LEFT]);
	}
	/*
	for (int i = 0; i < mWidthTiles; i++)
	{
		TextureWorker::renderTextureRegion(mTextureWalls, getRightWallTileOnSpecificPositionIsoCoord(i), &mTextureWalls.getTextureTypes()[(int)WallType::RIGHT]);
	}
	
	for (int j = 0; j < mHeightTiles - 1; j++)
	{
		TextureWorker::renderTextureRegion(mTextureWalls, getLeftWallTileOnSpecificPositionIsoCoord(j), &mTextureWalls.getTextureTypes()[(int)WallType::LEFT]);
	}
	*/

}

Coordinate2D World::getRightWallStartISOCoord()
{
	Coordinate2D res = getStartingPoint();

	res.setX(res.getX() + 0.5 * mTextureTiles.getWidthEachTextureTypeInPixels());
	res.setY(res.getY() - (mTextureWalls.getHeightEachTextureTypeInPixels() - 0.5 * mTextureTiles.getHeightEachTextureTypeInPixels()));

	return res;
}

Coordinate2D World::getLeftWallStartISOCoord()
{
	Coordinate2D res = getRightWallStartISOCoord();

	res.setX(res.getX() - mTextureWalls.getWidthEachTextureTypeInPixels());
	return res;
}

void World::render()
{
	renderFloor();
	renderStartFinishTiles();
	renderWalls();
}

Coordinate2D World::getRightWallTileOnSpecificPositionIsoCoord(int _position)
{
	Coordinate2D res = getRightWallStartISOCoord();
	IsometricEngine::convertIsometricTo2D(res);

	res.setX(res.getX() + _position * mTextureWalls.getWidthEachTextureTypeInPixels());
	res.setY(res.getY());
	IsometricEngine::convert2DtoIsometric(res);

	return res;
}

Coordinate2D World::getLeftWallTileOnSpecificPositionIsoCoord(int _position)
{
	Coordinate2D res = getLeftWallStartISOCoord();
	IsometricEngine::convertIsometricTo2D(res);

	res.setX(res.getX());
	res.setY(res.getY() + _position * mTextureWalls.getWidthEachTextureTypeInPixels());
	IsometricEngine::convert2DtoIsometric(res);

	return res;
}

Coordinate2D World::getTileOnSpecificPositionISOCoord(Coordinate2D _position)
{
	Coordinate2D res;
	Coordinate2D floorBegin = getStartingPoint();
	IsometricEngine::convertIsometricTo2D(floorBegin);

	res.setX(floorBegin.getX() + _position.getX() * (mTextureTiles.getWidthEachTextureTypeInPixels() / 2));
	res.setY(floorBegin.getY() + _position.getY() * (mTextureTiles.getHeightEachTextureTypeInPixels()));

	IsometricEngine::convert2DtoIsometric(res);

	return res;
}
