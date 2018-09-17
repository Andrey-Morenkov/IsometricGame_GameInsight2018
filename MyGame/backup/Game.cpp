#include "Game.h"
#include "TextureWorker.h"
#include "Settings.h"

Game & Game::Instance()
{
	static Game game;
	return game;
}

Game::Game()
{
	mIsometricEngine = new IsometricEngine();
}


Game::~Game()
{
	delete mIsometricEngine;
}

SDL_Event& Game::getEvent()
{
	return mEvent;
}

SDL_Rect Game::getMouseRect()
{
	return mMouseRect;
}

Point2D Game::getMousepoint()
{
	return mMousepoint;
}

Point2D Game::getMapScroll2DPosition()
{
	return mMapScroll2Dposition;
}

bool Game::getIsGameOver()
{
	return mIsGameOver;
}

int Game::getMapScrollSpeed()
{
	return mMapScrollSpeed;
}

int Game::getLastTileClicked()
{
	return mLastTileClicked;
}

IsometricEngine * Game::getIsometricEngine()
{
	return mIsometricEngine;
}

Texture & Game::getMousepointTexture()
{
	return mMousepointTexture;
}

Texture & Game::getTileTexture()
{
	return mTileTexture;
}

Texture & Game::getWallTexture()
{
	return mWallTexture;
}

vector<SDL_Rect>& Game::getMousepointTypes()
{
	return mMousepointTypes;
}

vector<SDL_Rect>& Game::getTileTypes()
{
	return mTileTypes;
}

vector<SDL_Rect>& Game::getWallTypes()
{
	return mWallTypes;
}

void Game::setMouseRect(SDL_Rect _mouseRect)
{
	mMouseRect = _mouseRect;
}

void Game::setMousepoint(Point2D _mousepoint)
{
	mMousepoint = _mousepoint;
}

void Game::setMapScroll2DPosition(Point2D _mapScroll2DPosition)
{
	mMapScroll2Dposition = _mapScroll2DPosition;
}

void Game::setIsGameOver(bool _isGameOver)
{
	mIsGameOver = _isGameOver;
}

void Game::setMapScrollSpeed(int _MapScrollSpeed)
{
	mMapScrollSpeed = _MapScrollSpeed;
}

void Game::setLastTileClicked(int _lastTileClicked)
{
	mLastTileClicked = _lastTileClicked;
}

void Game::generateWorld()
{
	Point2D point;
	Point2D wallPoint;

	int maptileType = -1;
	int wallType = -1;

	// Create map
	for (int i = 0; i < mIsometricEngine->getMapHeightTiles(); ++i)
	{
		for (int j = 0; j < mIsometricEngine->getMapWidthTiles(); ++j)
		{
			maptileType = 0; //we got only one texture for map tile now

			point.setX(mIsometricEngine->getScrollX() + (j * mIsometricEngine->getTileSize()));
			point.setY(mIsometricEngine->getScrollY() + (i * mIsometricEngine->getTileSize()));

			mIsometricEngine->convert2DtoIsometric(&point);

			if (i == 0 || j == 0)
			{
				wallPoint = point;
			}

			TextureWorker::renderTextureRegion(mTileTexture, point.getX(), point.getY(), &mTileTypes[maptileType]);
			
			if (i == 0)
			{
				// generate right walls

				wallType = 1; 
				wallPoint.setX(wallPoint.getX() + (0.5 * TILE_TEXTURE_WIDTH_IN_PIXELS));
				wallPoint.setY(wallPoint.getY() - (WALL_TEXTURE_HEIGHT_IN_PIXELS - 0.5 * (TILE_TEXTURE_HEIGHT_IN_PIXELS)));

				TextureWorker::renderTextureRegion(mWallTexture, wallPoint.getX(), wallPoint.getY(), &mWallTypes[wallType]);

				if (j == 0)
				{
					wallType = 0;
					wallPoint.setX(wallPoint.getX() - (0.5 * TILE_TEXTURE_WIDTH_IN_PIXELS));

					TextureWorker::renderTextureRegion(mWallTexture, wallPoint.getX(), wallPoint.getY(), &mWallTypes[wallType]);
				}
			}
			else
			{
				if (j == 0)
				{
					// generate left walls

					wallType = 0;
					//wallPoint.setX(wallPoint.getX() + (0.5 * TILE_TEXTURE_WIDTH_IN_PIXELS));
					wallPoint.setY(wallPoint.getY() - (WALL_TEXTURE_HEIGHT_IN_PIXELS - 0.5 * (TILE_TEXTURE_HEIGHT_IN_PIXELS)));

					TextureWorker::renderTextureRegion(mWallTexture, wallPoint.getX(), wallPoint.getY(), &mWallTypes[wallType]);
				}
			}
		}
	}
}
