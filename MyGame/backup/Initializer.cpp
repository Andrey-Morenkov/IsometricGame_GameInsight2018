#include "Initializer.h"
#include "Settings.h"
#include "SDL_image.h"
#include "SupportMacroses.h"
#include "Game.h"
#include "Core.h"
#include "TextureWorker.h"

void initSDLstuff(SDL_Window *& _window, SDL_Renderer *& _renderer, string _windowName)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != (int)ResultCode::SUCCESS)
	{
		LOG_CRITICAL("Something went wrong in SDL_Init. Error: %s.Immediate Exit.", SDL_GetError());
		exit((int)ResultCode::ERROR);
	}

	if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
	{
		LOG_ERROR("Linear texture filtering was not enabled! Error: %s. Continue without it.", SDL_GetError());
	}

	_window = SDL_CreateWindow(
		_windowName.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		MAIN_WINDOW_WIDTH,
		MAIN_WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL
	);

	POINTER_VALIDATION(_window);
	LOG_INFO("Successfully created window %p", _window);

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	POINTER_VALIDATION(_renderer);
	LOG_INFO("Successfully created renderer %p for window %p", _renderer, _window);

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		LOG_CRITICAL("Something went wrong in IMG_Init. Error: %s.Immediate Exit.", SDL_GetError());
		exit((int)ResultCode::ERROR);
	}
	LOG_INFO("Successfully initialized image library for PNG");
}

void initGame()
{
	Game::Instance().setIsGameOver(false);	
	Game::Instance().setMapScroll2DPosition(Point2D(-77, 0));
	Game::Instance().setMapScrollSpeed(3);
	Game::Instance().setLastTileClicked(-1);

	// setup isometric engine
	Game::Instance().getIsometricEngine()->setTileSize(TILE_SIZE_IN_PIXELS);
	Game::Instance().getIsometricEngine()->setMapSize(MAP_WIDTH_TILES, MAP_HEIGHT_TILES);
	Game::Instance().getIsometricEngine()->setScrollX(77);
	Game::Instance().getIsometricEngine()->setScrollY(-77);

	// load and setup   textures
	//     load mouse   textures
	Game::Instance().getMousepointTexture().loadTextureFromImageFile(MOUSE_TEXTURE_PATH);
	TextureWorker::findTexturesTypesFromWholeTexture(Game::Instance().getMousepointTexture(), MOUSE_TEXTURE_WIDTH_IN_PIXELS, MOUSE_TEXTURE_HEIGHT_IN_PIXELS, Game::Instance().getMousepointTypes());
	
	//     load maptile textures
	Game::Instance().getTileTexture().loadTextureFromImageFile(TILE_TEXTURE_PATH);
	TextureWorker::findTexturesTypesFromWholeTexture(Game::Instance().getTileTexture(), TILE_TEXTURE_WIDTH_IN_PIXELS, TILE_TEXTURE_HEIGHT_IN_PIXELS, Game::Instance().getTileTypes());

	//     load wall textures
	Game::Instance().getWallTexture().loadTextureFromImageFile(WALL_TEXTURE_PATH);
	TextureWorker::findTexturesTypesFromWholeTexture(Game::Instance().getWallTexture(), WALL_TEXTURE_WIDTH_IN_PIXELS, WALL_TEXTURE_HEIGHT_IN_PIXELS, Game::Instance().getWallTypes());
}