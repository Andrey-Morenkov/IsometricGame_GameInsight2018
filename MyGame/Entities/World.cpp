#include "World.h"
#include "../Settings.h"
#include "../Core.h"
#include "../SupportMacroses.h"
#include "../TextureWorker.h"

World::World()
{
	mWidthTiles = 0;
	mHeightTiles = 0;
	setStartingPoint(Coordinate2D(0, 0));
	
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

Coordinate2D & World::getStartingPointLink()
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
	Coordinate2D floorBegin = getStartingPoint();
	IsometricEngine::convertIsometricTo2D(floorBegin);

	res.setX(floorBegin.getX() + _incomintMapCoordinates.getX() * ((double)mTextureTiles.getWidthEachTextureTypeInPixels() / 2.0));
	res.setY(floorBegin.getY() + _incomintMapCoordinates.getY() * (mTextureTiles.getHeightEachTextureTypeInPixels()));
	IsometricEngine::convert2DtoIsometric(res);
	return res;
}

Coordinate2D World::getTileMapCoordinatesFromISOCoords(Coordinate2D _incomingISOCoordinates)
{
	double isoLeftLineCoeff = -0.5;
	double isoRightLineCoeff = 0.5;
	int lineStepX = TILE_SIZE_IN_PIXELS;
	int lineStepY = TILE_SIZE_IN_PIXELS - 1;
	//LOG_INFO("World begin (%d,%d)", mPosition.getX(), mPosition.getY());
	//LOG_INFO("Incoming coordinates (%d,%d)", _incomingISOCoordinates.getX(), _incomingISOCoordinates.getY());

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

	//LOG_INFO("Render walls. Starting point = (%d,%d), walls begin 2D = (%d,%d)", mStartingPoint.getX(), mStartingPoint.getY(), wallsBeginRight.getX(), wallsBeginRight.getY());

	//LOG_INFO("Render walls. Corrected wallsR begin 2D = (%d,%d)", wallsBeginRight.getX(), wallsBeginRight.getY());
	//LOG_INFO("Render walls. Corrected wallsL begin 2D = (%d,%d)", wallsBeginLeft.getX(), wallsBeginLeft.getY());

	for (int i = 0; i < mWidthTiles; i++)
	{
		currentPoint.setX(wallsBeginRight.getX() + i * mTextureWalls.getWidthEachTextureTypeInPixels());
		currentPoint.setY(wallsBeginRight.getY());
		//LOG_INFO("Render walls. i = %d, current point = (%d, %d)", i, currentPoint.getX(), currentPoint.getY());
		IsometricEngine::convert2DtoIsometric(currentPoint);
		//LOG_INFO("Render walls. Isometric point = (%d,%d)", currentPoint.getX(), currentPoint.getY());
		TextureWorker::renderTextureRegion(mTextureWalls, currentPoint, &mTextureWalls.getTextureTypes()[(int)WallType::RIGHT]);
	}
	
	for (int j = 0; j < mHeightTiles - 1; j++)
	{
		currentPoint.setX(wallsBeginLeft.getX());
		currentPoint.setY(wallsBeginLeft.getY() + j * (mTextureWalls.getWidthEachTextureTypeInPixels()));
		//LOG_INFO("Render walls. j = %d, current point = (%d, %d)", j, currentPoint.getX(), currentPoint.getY());
		IsometricEngine::convert2DtoIsometric(currentPoint);
		//LOG_INFO("Render walls. Isometric point = (%d,%d)", currentPoint.getX(), currentPoint.getY());
		TextureWorker::renderTextureRegion(mTextureWalls, currentPoint, &mTextureWalls.getTextureTypes()[(int)WallType::LEFT]);
	}
}

void World::render()
{
	renderFloor();
	renderWalls();
}