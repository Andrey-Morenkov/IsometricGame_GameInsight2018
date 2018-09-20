#include "Cannon.h"
#include "../TextureWorker.h"
#include "../Settings.h"

void Cannon::loadTexture()
{
	mSelfTexture.setWidthEachTextureTypeInPixels(CANNON_TEXTURE_WIDTH_IN_PIXELS);
	mSelfTexture.setHeightEachTextureTypeInPixels(CANNON_TEXTURE_HEIGHT_IN_PIXELS);
	mSelfTexture.loadFromPath(CANNON_TEXTURE_PATH);
}

Cannon::Cannon()
{
	loadTexture();
	mTimeExeInSec = CANNON_SHOTS_PER_MIN;
}

Cannon::Cannon(Coordinate2D _startCoord) : Cannon()
{
	mPosition = _startCoord;
}

Cannon::~Cannon()
{
}

void Cannon::setType(WallType _type)
{
	mType = _type;
}

WallType Cannon::getType()
{
	return mType;
}

void Cannon::render()
{
	TextureWorker::renderTextureRegion(mSelfTexture, mPosition, &mSelfTexture.getTextureTypes()[(int)mType]);
}

bool Cannon::fire()
{
	return isNeedToExe();
}

