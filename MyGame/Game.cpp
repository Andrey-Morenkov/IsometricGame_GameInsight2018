#include "Game.h"
#include "Settings.h"

void Game::setPlayerSpawnpoint(Coordinate2D _spawnpointMapCoods)
{
	mPlayer.second = _spawnpointMapCoods;
}

void Game::changeStartingPoint(Coordinate2D _newStartingPoint)
{
	mWorld->setStartingPoint(_newStartingPoint);
	mUpdateAllEntityCoordinates();
}

void Game::mUpdateAllEntityCoordinates()
{
	Coordinate2D newPos = mWorld->getTileISOCoordinatesFromMapCoords(mPlayer.second);
	mPlayer.first->setPositionFromTileIsoCoords(newPos);

	for (int i = 0; i < mNPCs.size(); i++)
	{
		newPos = mWorld->getTileISOCoordinatesFromMapCoords(mNPCs[i].second);
		// TO DO NPC
	}

	for (int i = 0; i < mBarriers.size(); i++)
	{
		newPos = mWorld->getTileISOCoordinatesFromMapCoords(mBarriers[i].second);
		// TO DO NPC
	}
	for (int i = 0; i < mCannons.size(); i++)
	{
		newPos = mWorld->getTileISOCoordinatesFromMapCoords(mCannons[i].second);
		// TO DO NPC
	}
}

Game::Game()
{
	mWorld = nullptr;
	mMouseCursor = nullptr;
	mIsGameOver = false;
}

Game::~Game()
{
	delete mWorld;
	delete mMouseCursor;
	delete mPlayer.first;
}

void Game::createNewGame()
{
	mWorld = new World(MAP_WIDTH_TILES, MAP_HEIGHT_TILES);
	mMouseCursor = new MouseCursor();

	Player* currPlayer = new Player();
	Coordinate2D playerStartCoord = Coordinate2D(0, 0);

	mPlayer.first = currPlayer;
	mPlayer.second = playerStartCoord;
}

bool Game::isGameOver()
{
	return mIsGameOver;
}

void Game::setGameOver(bool _newState)
{
	mIsGameOver = _newState;
}
