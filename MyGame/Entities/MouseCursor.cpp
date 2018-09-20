#include "MouseCursor.h"
#include "../Settings.h"
#include "../TextureWorker.h"

void MouseCursor::loadTexture()
{
	mSelfTexture.setWidthEachTextureTypeInPixels(MOUSE_TEXTURE_WIDTH_IN_PIXELS);
	mSelfTexture.setHeightEachTextureTypeInPixels(MOUSE_TEXTURE_HEIGHT_IN_PIXELS);
	mSelfTexture.loadFromPath(MOUSE_TEXTURE_PATH);
}

MouseCursor::MouseCursor()
{
	loadTexture();
	isCorrect = true;
}

MouseCursor::~MouseCursor()
{
}

void MouseCursor::render()
{
	TextureWorker::renderTextureRegion(mSelfTexture, mPosition, &mSelfTexture.getTextureTypes()[(int)TileType::DEFAULT]);
}

void MouseCursor::setIsCorrect(bool _newState)
{
	isCorrect = _newState;
}

bool MouseCursor::getIsCorrect()
{
	return isCorrect;
}
