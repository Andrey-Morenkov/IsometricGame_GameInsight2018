#pragma once
#include "ResultCode.h"
#include "Point2D.h"

#define DEFAULT_TILE_SIZE  32
#define DEFAULT_MAP_WIDTH  30
#define DEFAULT_MAP_HEIGHT 30

class IsometricEngine
{
private:

	int mScrollX;
	int mScrollY;
	int mMapWidthTiles;
	int mMapHeightTiles;
	int mTileSize;

public:
	
	IsometricEngine();
	IsometricEngine(int _tileSize);
	~IsometricEngine();

	void setScrollX(int _scrollX);
	void setScrollY(int _scrollY);
	void setMapWidthTiles(int _mapWidthTiles);
	void setMapHeightTiles(int _mapHeightTiles);
	void setTileSize(int _tileSize);
	void setMapSizeInTiles(int _widthTiles, int _heightTiles);

	int getScrollX();
	int getScrollY();
	int getMapWidthTiles();
	int getMapHeightTiles();
	int getTileSize();

	void setMapSize(int _width, int _height);
	void convert2DtoIsometric(Point2D* _point);
	void convertIsometricTo2D(Point2D* _point);
	void getTileCoordinates(Point2D* _point, Point2D* _point2Dcoord);
};

