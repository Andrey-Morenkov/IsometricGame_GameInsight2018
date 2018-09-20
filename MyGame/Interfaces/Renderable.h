#pragma once

#include <string>

#include "../Texture.h"

class Renderable
{
protected:

	Texture mSelfTexture;

	virtual void loadTexture() = 0;

public:

	virtual void render() = 0;

	Texture& getSelfTexture();
};