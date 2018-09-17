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
	mPosition = mWorld->getTileISOCoordinates(mPosition);
}

void MouseCursor::render()
{
	getMouseTileClick();
	if ((mPosition.getX() >= 0) && (mPosition.getY() >= 0))
	{
		TextureWorker::renderTextureRegion(mTextureCursor, mPosition, &mTextureCursor.getTextureTypes()[(int)TileType::DEFAULT]);
	}	
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
	//LOG_ERROR("New mouse position OLD = (%d,%d), NEW = (%d,%d)", mPosition.getX(), mPosition.getY(), _newPosition.getX(), _newPosition.getY());
	mPosition = _newPosition;
}
