#include <string>

#include "IsometricEngine.h"
#include "SupportMacroses.h"
#include "ResultCode.h"
#include "SDL_log.h"
#include "SDL.h"

using namespace std;

IsometricEngine::IsometricEngine()
{
	mScrollX   = 0;
	mScrollY   = 0;
	mMapWidthTiles  = 0;
	mMapHeightTiles = 0;
	mTileSize  = DEFAULT_TILE_SIZE;
}

IsometricEngine::IsometricEngine(int _tileSize = DEFAULT_TILE_SIZE)
{
	INT_MUST_BE_GREATER_THAN_ZERO(_tileSize);

	mScrollX   = 0;
	mScrollY   = 0;
	mMapWidthTiles = 0;
	mMapHeightTiles = 0;
	mTileSize = _tileSize;
}


IsometricEngine::~IsometricEngine()
{
}

void IsometricEngine::setScrollX(int _scrollX)
{
	mScrollX = _scrollX;
}

void IsometricEngine::setScrollY(int _scrollY)
{
	mScrollY = _scrollY;
}

void IsometricEngine::setMapWidthTiles(int _mapWidthTiles)
{
	mMapWidthTiles = _mapWidthTiles;
}

void IsometricEngine::setMapHeightTiles(int _mapHeightTiles)
{
	mMapHeightTiles = _mapHeightTiles;
}

void IsometricEngine::setTileSize(int _tileSize)
{
	mTileSize = _tileSize;
}

void IsometricEngine::setMapSizeInTiles(int _widthTiles, int _heightTiles)
{
	INT_MUST_BE_GREATER_THAN_ZERO(_widthTiles);
	INT_MUST_BE_GREATER_THAN_ZERO(_heightTiles);

	mMapWidthTiles = _widthTiles;
	mMapHeightTiles = _heightTiles;
}

int IsometricEngine::getScrollX()
{
	return mScrollX;
}

int IsometricEngine::getScrollY()
{
	return mScrollY;
}

int IsometricEngine::getMapWidthTiles()
{
	return mMapWidthTiles;
}

int IsometricEngine::getMapHeightTiles()
{
	return mMapHeightTiles;
}

int IsometricEngine::getTileSize()
{
	return mTileSize;
}

void IsometricEngine::setMapSize(int _mapWidthTiles = DEFAULT_MAP_WIDTH, int _mapHeightTiles = DEFAULT_MAP_HEIGHT)
{
	INT_MUST_BE_GREATER_THAN_ZERO(_mapWidthTiles);
	INT_MUST_BE_GREATER_THAN_ZERO(_mapHeightTiles);

	mMapWidthTiles = _mapWidthTiles;
	mMapHeightTiles = _mapHeightTiles;
}

void IsometricEngine::convert2DtoIsometric(Point2D* _point)
{
	POINTER_VALIDATION(_point);

	//LOG_INFO("Incoming 2D point params: x = %d, y = %d", _point->getX(), _point->getY());

	int tmpX = _point->getX() - _point->getY();
	int tmpY = (_point->getX() + _point->getY())*0.5;
	_point->setX(tmpX);
	_point->setY(tmpY);

	//LOG_INFO("New isometric point params: x = %d, y = %d", _point->getX(), _point->getY());
}

void IsometricEngine::convertIsometricTo2D(Point2D * _point)
{
	POINTER_VALIDATION(_point);

	int tmpX = (2 * _point->getY() + _point->getX())*0.5;
	int tmpY = (2 * _point->getY() - _point->getX())*0.5;
	_point->setX(tmpX);
	_point->setY(tmpY);
}

void IsometricEngine::getTileCoordinates(Point2D* _point, Point2D* _point2Dcoord)
{
	POINTER_VALIDATION(_point);
	POINTER_VALIDATION(_point2Dcoord);
	INT_MUST_BE_GREATER_THAN_ZERO(mTileSize);

	float tempX = (float)_point->getX() / (float)mTileSize;
	float tempY = (float)_point->getY() / (float)mTileSize;
	_point2Dcoord->setX((int)tempX);
	_point2Dcoord->setY((int)tempY);
}
