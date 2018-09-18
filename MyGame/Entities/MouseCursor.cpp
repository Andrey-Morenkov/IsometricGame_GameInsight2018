#include "MouseCursor.h"
#include "../Settings.h"
#include "../TextureWorker.h"

MouseCursor::MouseCursor()
{
	mTextureCursor.setWidthEachTextureTypeInPixels(MOUSE_TEXTURE_WIDTH_IN_PIXELS);
	mTextureCursor.setHeightEachTextureTypeInPixels(MOUSE_TEXTURE_HEIGHT_IN_PIXELS);
	mTextureCursor.loadFromPath(MOUSE_TEXTURE_PATH);
	isCorrect = true;
}

MouseCursor::~MouseCursor()
{
}


void MouseCursor::render()
{
	TextureWorker::renderTextureRegion(mTextureCursor, mPosition, &mTextureCursor.getTextureTypes()[(int)TileType::DEFAULT]);
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

void MouseCursor::setIsCorrect(bool _newState)
{
	isCorrect = _newState;
}

bool MouseCursor::getIsCorrect()
{
	return isCorrect;
}
