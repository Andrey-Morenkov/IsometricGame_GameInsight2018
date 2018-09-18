#include "Game.h"
#include "Settings.h"
#include "ResultCode.h"

void Game::setPlayerSpawnpoint(Coordinate2D _spawnpointMapCoods)
{
	mPlayer.second = _spawnpointMapCoods;
}

void Game::changeStartingPoint(Coordinate2D _newStartingPoint)
{
	mWorld->setStartingPoint(_newStartingPoint);
	mUpdateAllEntityCoordinates();
}

int Game::getBarrierPositionByMapCoord(Coordinate2D _possibleBarrierMapCoords)
{
	for (int i = 0; i < mBarriers.size(); i++)
	{
		if (mBarriers[i].second == _possibleBarrierMapCoords)
		{
			return i;
		}
	}
	return (int)ResultCode::NOT_EXIST;
}

ExitReason Game::getExitReason()
{
	return mWhyExit;
}

void Game::setExitReason(ExitReason _reason)
{
	mWhyExit = _reason;
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
		mBarriers[i].first->setPosition(newPos);
	}
	for (int i = 0; i < mCannons.size(); i++)
	{
		newPos = mWorld->getTileISOCoordinatesFromMapCoords(mCannons[i].second);
		// TO DO Cannons
	}
}

Game::Game()
{
	mWorld = nullptr;
	mMouseCursor = nullptr;
	mIsGameOver = false;
	mWhyExit = ExitReason::QUIT;
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

	mWorldMap.setWorldSize(Vec2i(MAP_WIDTH_TILES, MAP_HEIGHT_TILES));
	mWorldMap.setHeuristic(AStar::Heuristic::euclidean);
	mWorldMap.setDiagonalMovement(ALLOW_DIAGONAL_MOVEMENT);
}

bool Game::isGameOver()
{
	return mIsGameOver;
}

void Game::setGameOver(bool _newState)
{
	mIsGameOver = _newState;
}
