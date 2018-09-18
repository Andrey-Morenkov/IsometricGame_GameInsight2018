#pragma once

#include <vector>
#include <string>

#include "SDL.h"

using namespace std;

class Texture
{
private:

	unsigned int mWidthWholeTextureInPixels;
	unsigned int mHeightWholeTextureInPixels;
	unsigned int mWidthEachTextureTypeInPixels;
	unsigned int mHeightEachTextureTypeInPixels;
	string mFilePath;

	SDL_Texture*     mTextureImage;
	vector<SDL_Rect> mTextureTypes;

	void divideIntoTextureTypes();

public:

	Texture();
	Texture(unsigned int _wholeTextureWidthInPixels, unsigned int _wholeTextureHeightInPixels, unsigned int _eachTextureTypeWidthInPixels, unsigned int _eachTextureTypeHeightInPixels);
	Texture(unsigned int _wholeTextureWidthInPixels, unsigned int _wholeTextureHeightInPixels);
	~Texture();

	unsigned int getWidthWholeTextureInPixels();
	unsigned int getHeightWholeTextureInPixels();
	unsigned int getWidthEachTextureTypeInPixels();
	unsigned int getHeightEachTextureTypeInPixels();
	SDL_Texture* getTextureImage();
	vector<SDL_Rect>& getTextureTypes();

	void setWidthEachTextureTypeInPixels(int _widthEach);
	void setHeightEachTextureTypeInPixels(int _heightEach);

	void loadFromPath(string _filepath);
};

