#include "MouseCursor.h"
#include "Settings.h"
#include "TextureWorker.h"

MouseCursor::MouseCursor()
{
	mTextureCursor.setWidthEachTextureTypeInPixels(MOUSE_TEXTURE_WIDTH_IN_PIXELS);
	mTextureCursor.setHeightEachTextureTypeInPixels(MOUSE_TEXTURE_HEIGHT_IN_PIXELS);
	mTextureCursor.loadFromPath(MOUSE_TEXTURE_PATH);
}

MouseCursor::MouseCursor(World * _world) : MouseCursor()
{
	mWorld = _world;
}

MouseCursor::~MouseCursor()
{
}

void MouseCursor::getMouseTileClick()
{
	Coordinate2D startPoint;
	Coordinate2D currPoint;

	startPoint = mWorld->getStartingPoint();
	currPoint = mPosition;
	
	IsometricEngine::convertIsometricTo2D(startPoint);
	IsometricEngine::convertIsometricTo2D(currPoint);

	mLastTileClicked.setX((currPoint.getX() - startPoint.getX()) / (TILE_TEXTURE_WIDTH_IN_PIXELS / 2));
	mLastTileClicked.setY((currPoint.getY() - startPoint.getY()) / (TILE_TEXTURE_HEIGHT_IN_PIXELS / 2));
	//LOG_INFO("CLicked tile (%d,%d)", mLastTileClicked.getX(), mLastTileClicked.getY());
}

void MouseCursor::render()
{
	getMouseTileClick();

	Coordinate2D renderPoint;
	Coordinate2D isoStart = mWorld->getStartingPoint();
	IsometricEngine::convertIsometricTo2D(isoStart);

	renderPoint.setX(isoStart.getX() + mLastTileClicked.getX() * (TILE_SIZE_IN_PIXELS / 1.0));
	renderPoint.setY(isoStart.getY() + mLastTileClicked.getY() * (TILE_SIZE_IN_PIXELS));

	//LOG_INFO("Render floor. i = %d, j = %d, current point = (%d, %d)", i, j, currentPoint.getX(), currentPoint.getY());
	IsometricEngine::convert2DtoIsometric(renderPoint);
	//LOG_INFO("Render floor. Isometric point = (%d,%d)", currentPoint.getX(), currentPoint.getY());
	TextureWorker::renderTextureRegion(mTextureCursor, renderPoint, &mTextureCursor.getTextureTypes()[(int)TileType::DEFAULT]);
}

World * MouseCursor::getLocation()
{
	return mWorld;
}

void MouseCursor::setLocation(World * _world)
{
	mWorld = _world;
}

Texture& MouseCursor::getTextureCursor()
{
	return mTextureCursor;
}

Coordinate2D MouseCursor::getPosition()
{
	return mPosition;
}

void MouseCursor::setPosition(Coordinate2D _newPosition)
{
	mPosition = _newPosition;
}
