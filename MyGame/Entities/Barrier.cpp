#include "Barrier.h"
#include "../Settings.h"
#include "../TextureWorker.h"

int Barrier::getRandomTexture()
{
	return (rand() % mTextureBarrier.getTextureTypes().size());
}

Barrier::Barrier()
{
	mTextureBarrier.setWidthEachTextureTypeInPixels(BARRIER_TEXTURE_WIDTH_IN_PIXELS);
	mTextureBarrier.setHeightEachTextureTypeInPixels(BARRIER_TEXTURE_HEIGHT_IN_PIXELS);
	mTextureBarrier.loadFromPath(BARRIER_TEXTURE_PATH);
	mTextureType = getRandomTexture();
}


Barrier::~Barrier()
{
}

void Barrier::render()
{
	TextureWorker::renderTextureRegion(mTextureBarrier, mPosition, &mTextureBarrier.getTextureTypes()[mTextureType]);
}

Texture & Barrier::getTextureBarrier()
{
	return mTextureBarrier;
}

Coordinate2D Barrier::getPosition()
{
	return mPosition;
}

void Barrier::setPosition(Coordinate2D _newPosition)
{
	mPosition = _newPosition;
}
