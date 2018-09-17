#pragma once

#include <string>

#include "SDL.h"
#include "ResultCode.h"

using namespace std;

class Texture
{
private:

	int mX;
	int mY;
	int mWidth;
	int mHeight;
	double mAngle;
	SDL_Point* mCenter;
	SDL_Rect* mClipRect;
	SDL_RendererFlip mFlipType;
	SDL_Texture* mSDLTexture;
	string mFilePath;

public:

	Texture();
	~Texture();

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	double getAngle();
	SDL_Point* getCenter();
	SDL_Rect* getClipRect();
	SDL_RendererFlip getFlipType();
	SDL_Texture* getSDLTexture();
	string getFilePath();

	void setX(int _x);
	void setY(int _y);
	void setWidth(int _width);
	void setHeight(int _height);
	void setAngle(double _angle);
	void setCenter(SDL_Point* _center);
	void setClipRect(SDL_Rect* _clipRect);
	void setFlipType(SDL_RendererFlip _flipType);
	void setSDLTexture(SDL_Texture* _SDLTexture);
	void setFilePath(string _filePath);
	void initialize(int _x, int _y, double _angle, SDL_Point* _center, SDL_Rect* _clipRect, SDL_RendererFlip _flipType);
	void loadTextureFromImageFile(string _fileName);
};

