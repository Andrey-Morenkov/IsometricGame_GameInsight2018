#include <vector>
#include <string>

#include "SDL.h"
#include "ResultCode.h"
#include "SupportMacroses.h"
#include "Texture.h"
#include "Core.h"

namespace TextureWorker
{
	void findTexturesTypesFromWholeTexture(Texture& _wholeTexture, int _eachTextureWidth, int _eachTextureHeight, std::vector<SDL_Rect>& _findedTexturesTypes)
	{
		CONTAINER_MUST_BE_EMPTY(_findedTexturesTypes);
		INT_MUST_BE_GREATER_THAN_ZERO(_eachTextureWidth);
		INT_MUST_BE_GREATER_THAN_ZERO(_eachTextureHeight);
		INT_MUST_BE_GREATER_THAN_ZERO(_wholeTexture.getWidth());

		SDL_Rect singleTexture;
		singleTexture.x = 0;
		singleTexture.y = 0;
		singleTexture.w = _eachTextureWidth;
		singleTexture.h = _eachTextureHeight;

		while ((singleTexture.x + _eachTextureWidth) <= _wholeTexture.getWidth())
		{
			_findedTexturesTypes.push_back(SDL_Rect(singleTexture));
			singleTexture.x += _eachTextureWidth;
		}

		LOG_INFO("Finded %d texture types in texture %s", _findedTexturesTypes.size(), _wholeTexture.getFilePath().c_str());
	}

	void renderTextureRegion(Texture& _texture, int _x, int _y, SDL_Rect* _optionalTextureRegion = nullptr)
	{
		SDL_Rect renderRegion;
		renderRegion.x = _x;
		renderRegion.y = _y;

		if (_optionalTextureRegion != nullptr)
		{
			renderRegion.w = _optionalTextureRegion->w;
			renderRegion.h = _optionalTextureRegion->h;
		}
		else
		{
			renderRegion.w = _texture.getWidth();
			renderRegion.h = _texture.getHeight();
		}

		SDL_RenderCopyEx(mainRenderer, _texture.getSDLTexture(), _optionalTextureRegion, &renderRegion, _texture.getAngle(), _texture.getCenter(), _texture.getFlipType());
	}
}