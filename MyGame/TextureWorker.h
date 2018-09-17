#pragma once

#include <vector>
#include <string>

#include "SDL.h"
#include "ResultCode.h"
#include "SupportMacroses.h"
#include "Texture.h"
#include "Coordinate2D.h"

namespace TextureWorker
{
	void renderTextureRegion(Texture& _texture, Coordinate2D _pos, SDL_Rect* _optionalTextureRegion);
}
