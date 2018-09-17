#include "World.h"
#include "Settings.h"
#include "Core.h"
#include "SupportMacroses.h"
#include "TextureWorker.h"

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

void World::getTileCoordinates(Coordinate2D & _incomingCoordinates, Coordinate2D & _tileCoordinates)
{
	float tempX = (float)_incomingCoordinates.getX() / (float)TILE_SIZE_IN_PIXELS;
	float tempY = (float)_incomingCoordinates.getY() / (float)TILE_SIZE_IN_PIXELS;
	_tileCoordinates.setX((int)tempX);
	_tileCoordinates.setY((int)tempY);
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
