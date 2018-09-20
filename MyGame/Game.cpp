#include "Game.h"
#include "Settings.h"
#include "ResultCode.h"

void Game::setPlayerSpawnpoint(Coordinate2D _spawnpointMapCoods)
{
	mPlayer.second = _spawnpointMapCoods;
	mPlayer.first->setPositionFromTileIsoCoords(mWorld->getTileISOCoordinatesFromMapCoords(mPlayer.second));
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
		mNPCs[i].first->setPositionFromTileIsoCoords(newPos);
	}

	for (int i = 0; i < mBarriers.size(); i++)
	{
		newPos = mWorld->getTileISOCoordinatesFromMapCoords(mBarriers[i].second);
		mBarriers[i].first->setPosition(newPos);
	}
	for (int i = 0; i < mCannons.size(); i++)
	{
		switch (mCannons[i].first->getType())
		{
			case WallType::RIGHT:
			{
				newPos = mWorld->getRightWallTileOnSpecificPositionIsoCoord(mCannons[i].second);
				mCannons[i].first->setPosition(newPos);
				break;
			}
			case WallType::LEFT:
			{
				newPos = mWorld->getRightWallTileOnSpecificPositionIsoCoord(mCannons[i].second);
				mCannons[i].first->setPosition(newPos);
				break;
			}
		}
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

	mPlayer.first = new Player();
	mPlayer.second = MAP_LEFT_DOWN_CORNER;
	mPlayer.first->setPositionFromTileIsoCoords(mWorld->getTileISOCoordinatesFromMapCoords(MAP_LEFT_DOWN_CORNER));

	mWorldMap.setWorldSize({ MAP_WIDTH_TILES, MAP_HEIGHT_TILES });
	mWorldMap.setHeuristic(AStar::Heuristic::euclidean);
	mWorldMap.setDiagonalMovement(IS_ALLOW_DIAGONAL_MOVEMENT);
	changeStartingPoint(Coordinate2D(100, 100));
}

bool Game::isGameOver()
{
	return mIsGameOver;
}

void Game::setGameOver(bool _newState)
{
	mIsGameOver = _newState;
}
