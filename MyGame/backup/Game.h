#pragma once

#include <vector>

#include "ResultCode.h"
#include "SDL.h"
#include "Point2D.h"
#include "IsometricEngine.h"
#include "Texture.h"

using namespace std;

class Game
{
private:

	SDL_Event mEvent;
	SDL_Rect  mMouseRect;
	Point2D   mMousepoint;
	Point2D   mMapScroll2Dposition;
	bool      mIsGameOver;
	int       mMapScrollSpeed;
	int       mLastTileClicked;
	IsometricEngine* mIsometricEngine;
	Texture   mMousepointTexture;
	Texture   mTileTexture;
	Texture   mWallTexture;
	vector<SDL_Rect> mMousepointTypes;
	vector<SDL_Rect> mTileTypes;
	vector<SDL_Rect> mWallTypes;

	Game();
	~Game();
	Game(Game const&) = delete;
	Game& operator= (Game const&) = delete;

public:

	static Game& Instance();

	SDL_Event& getEvent();
	SDL_Rect getMouseRect();
	Point2D getMousepoint();
	Point2D getMapScroll2DPosition();
	bool getIsGameOver();
	int getMapScrollSpeed();
	int getLastTileClicked();
	IsometricEngine* getIsometricEngine();
	Texture& getMousepointTexture();
	Texture& getTileTexture();
	Texture& getWallTexture();
	vector<SDL_Rect>& getMousepointTypes();
	vector<SDL_Rect>& getTileTypes();
	vector<SDL_Rect>& getWallTypes();

	void setMouseRect(SDL_Rect _mouseRect);
	void setMousepoint(Point2D _mousepoint);
	void setMapScroll2DPosition(Point2D _mapScroll2DPosition);
	void setIsGameOver(bool _isGameOver);
	void setMapScrollSpeed(int _MapScrollSpeed);
	void setLastTileClicked(int _lastTileClicked);

	void generateWorld();
};

