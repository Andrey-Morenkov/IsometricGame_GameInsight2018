#include "SDL_image.h"

#include "Texture.h"
#include "SupportMacroses.h"
#include "SDL_log.h"
#include "Core.h"


Texture::Texture()
{
	this->setX(0);
	this->setY(0);
	this->setAngle(0);
	this->setCenter(nullptr);
	this->setClipRect(nullptr);
	this->setFlipType(SDL_FLIP_NONE);
}


Texture::~Texture()
{
}

int Texture::getX()
{
	return mX;
}

int Texture::getY()
{
	return mY;
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}

double Texture::getAngle()
{
	return mAngle;
}

SDL_Point * Texture::getCenter()
{
	return mCenter;
}

SDL_Rect * Texture::getClipRect()
{
	return mClipRect;
}

SDL_RendererFlip Texture::getFlipType()
{
	return mFlipType;
}

SDL_Texture * Texture::getSDLTexture()
{
	return mSDLTexture;
}

string Texture::getFilePath()
{
	return mFilePath;
}

void Texture::setX(int _x)
{
	mX = _x;
}

void Texture::setY(int _y)
{
	mY = _y;
}

void Texture::setWidth(int _width)
{
	mWidth = _width;
}

void Texture::setHeight(int _height)
{
	mHeight = _height;
}

void Texture::setAngle(double _angle)
{
	mAngle = _angle;
}

void Texture::setCenter(SDL_Point * _center)
{
	mCenter = _center;
}

void Texture::setClipRect(SDL_Rect * _clipRect)
{
	mClipRect = _clipRect;
}

void Texture::setFlipType(SDL_RendererFlip _flipType)
{
	mFlipType = _flipType;
}

void Texture::setSDLTexture(SDL_Texture * _SDLTexture)
{
	mSDLTexture = _SDLTexture;
}

void Texture::setFilePath(string _filePath)
{
	mFilePath = string(_filePath);
}

void Texture::loadTextureFromImageFile(string _filePath)
{
	SDL_Surface *tmpSurface = IMG_Load(_filePath.c_str());

	POINTER_VALIDATION(tmpSurface);
	POINTER_VALIDATION(mainRenderer);
	
	this->setSDLTexture(SDL_CreateTextureFromSurface(mainRenderer, tmpSurface));

	POINTER_VALIDATION(getSDLTexture());

	this->setWidth(tmpSurface->w);
	this->setHeight(tmpSurface->h);
	this->setFilePath(_filePath);
	SDL_FreeSurface(tmpSurface);

	LOG_INFO("Successfully loaded texture from file %s, width = %d, height = %d", _filePath.c_str(), this->getWidth(), this->getHeight());
}

void Texture::initialize(int _x, int _y, double _angle, SDL_Point * _center, SDL_Rect * _clipRect, SDL_RendererFlip _flipType)
{
	this->setX(_x);
	this->setY(_y);
	this->setAngle(_angle);
	this->setCenter(_center);
	this->setFlipType(_flipType);
	this->setClipRect(_clipRect);
}
