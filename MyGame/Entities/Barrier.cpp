#include "Barrier.h"
#include "../Settings.h"
#include "../TextureWorker.h"

int Barrier::getRandomTexture()
{
	return (rand() % mSelfTexture.getTextureTypes().size());
}

void Barrier::loadTexture()
{
	mSelfTexture.setWidthEachTextureTypeInPixels(BARRIER_TEXTURE_WIDTH_IN_PIXELS);
	mSelfTexture.setHeightEachTextureTypeInPixels(BARRIER_TEXTURE_HEIGHT_IN_PIXELS);
	mSelfTexture.loadFromPath(BARRIER_TEXTURE_PATH);
}


Barrier::Barrier()
{
	loadTexture();
}


Barrier::~Barrier()
{
}

void Barrier::render()
{
	TextureWorker::renderTextureRegion(mSelfTexture, mPosition, &mSelfTexture.getTextureTypes()[getRandomTexture()]);
}
