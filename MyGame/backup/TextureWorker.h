#pragma once

#include <vector>
#include <string>

#include "SDL.h"
#include "ResultCode.h"
#include "SupportMacroses.h"
#include "Texture.h"

namespace TextureWorker
{
	void findTexturesTypesFromWholeTexture(Texture& _wholeTexture, int _eachTextureWidth, int _eachTextureHeight, std::vector<SDL_Rect>& _findedTexturesTypes);
	void renderTextureRegion(Texture& _texture, int _x, int _y, SDL_Rect* _optionalTextureRegion);
}
