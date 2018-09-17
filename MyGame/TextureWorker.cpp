#include <vector>
#include <string>

#include "SDL.h"
#include "ResultCode.h"
#include "SupportMacroses.h"
#include "Texture.h"
#include "Core.h"
#include "Coordinate2D.h"

namespace TextureWorker
{
	void renderTextureRegion(Texture& _texture, Coordinate2D _pos, SDL_Rect* _optionalTextureRegion = nullptr)
	{
		SDL_Rect renderRegion;
		renderRegion.x = _pos.getX();
		renderRegion.y = _pos.getY();

		if (_optionalTextureRegion != nullptr)
		{
			renderRegion.w = _optionalTextureRegion->w;
			renderRegion.h = _optionalTextureRegion->h;
		}
		else
		{
			renderRegion.w = _texture.getWidthWholeTextureInPixels();
			renderRegion.h = _texture.getHeightWholeTextureInPixels();
		}

		SDL_RenderCopyEx(mainRenderer, _texture.getTextureImage(), _optionalTextureRegion, &renderRegion, 0, 0, SDL_FLIP_NONE);
	}
}