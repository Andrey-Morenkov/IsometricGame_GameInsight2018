#include "Texture.h"
#include "SupportMacroses.h"
#include "SDL_image.h"
#include "SDL_log.h"
#include "Core.h"

Texture::Texture()
{
	mTextureImage = nullptr;
	mWidthEachTextureTypeInPixels = 0;
	mHeightEachTextureTypeInPixels = 0;
	mWidthWholeTextureInPixels = 0;
	mHeightWholeTextureInPixels = 0;
}

Texture::Texture(unsigned int _wholeTextureWidthInPixels, unsigned int _wholeTextureHeightInPixels, unsigned int _eachTextureTypeWidthInPixels, unsigned int _eachTextureTypeHeightInPixels)
{
	mTextureImage = nullptr;
	mWidthWholeTextureInPixels = _wholeTextureWidthInPixels;
	mHeightWholeTextureInPixels = _wholeTextureHeightInPixels;
	mWidthEachTextureTypeInPixels = _eachTextureTypeWidthInPixels;
	mHeightEachTextureTypeInPixels = _eachTextureTypeHeightInPixels;
}

Texture::Texture(unsigned int _wholeTextureWidthInPixels, unsigned int _wholeTextureHeightInPixels)
{
	mTextureImage = nullptr;
	mWidthWholeTextureInPixels = _wholeTextureWidthInPixels;
	mHeightWholeTextureInPixels = _wholeTextureHeightInPixels;
	mWidthEachTextureTypeInPixels = _wholeTextureWidthInPixels;
	mHeightEachTextureTypeInPixels = _wholeTextureHeightInPixels;
}


Texture::~Texture()
{
}

unsigned int Texture::getWidthWholeTextureInPixels()
{
	return mWidthWholeTextureInPixels;
}

unsigned int Texture::getHeightWholeTextureInPixels()
{
	return mHeightWholeTextureInPixels;
}

unsigned int Texture::getWidthEachTextureTypeInPixels()
{
	return mWidthEachTextureTypeInPixels;
}

unsigned int Texture::getHeightEachTextureTypeInPixels()
{
	return mHeightEachTextureTypeInPixels;
}

SDL_Texture * Texture::getTextureImage()
{
	return mTextureImage;
}

vector<SDL_Rect>& Texture::getTextureTypes()
{
	return mTextureTypes;
}

void Texture::setWidthEachTextureTypeInPixels(int _widthEach)
{
	mWidthEachTextureTypeInPixels = _widthEach;
}

void Texture::setHeightEachTextureTypeInPixels(int _heightEach)
{
	mHeightEachTextureTypeInPixels = _heightEach;
}

void Texture::divideIntoTextureTypes()
{
	CONTAINER_MUST_BE_EMPTY(mTextureTypes);
	INT_MUST_BE_GREATER_THAN_ZERO(mWidthEachTextureTypeInPixels);
	INT_MUST_BE_GREATER_THAN_ZERO(mHeightEachTextureTypeInPixels);
	INT_MUST_BE_GREATER_THAN_ZERO(mWidthWholeTextureInPixels);

	SDL_Rect singleTexture;
	singleTexture.x = 0;
	singleTexture.y = 0;
	singleTexture.w = mWidthEachTextureTypeInPixels;
	singleTexture.h = mHeightEachTextureTypeInPixels;

	while ((singleTexture.x + mWidthEachTextureTypeInPixels) <= mWidthWholeTextureInPixels)
	{
		mTextureTypes.push_back(SDL_Rect(singleTexture));
		singleTexture.x += mWidthEachTextureTypeInPixels;
	}

	LOG_INFO("Finded %d texture types in texture %s", mTextureTypes.size(), mFilePath.c_str());
}

void Texture::loadFromPath(string _filepath)
{
	mFilePath = _filepath;
	SDL_Surface *tmpSurface = IMG_Load(mFilePath.c_str());

	POINTER_VALIDATION(tmpSurface);
	POINTER_VALIDATION(mainRenderer);

	mTextureImage = SDL_CreateTextureFromSurface(mainRenderer, tmpSurface);

	POINTER_VALIDATION(getTextureImage());

	mWidthWholeTextureInPixels = tmpSurface->w;
	mHeightWholeTextureInPixels = tmpSurface->h;

	SDL_FreeSurface(tmpSurface);

	LOG_INFO("Successfully loaded texture from file %s, width = %d, height = %d", mFilePath.c_str(), this->getWidthWholeTextureInPixels(), this->getHeightWholeTextureInPixels());

	divideIntoTextureTypes();
}
