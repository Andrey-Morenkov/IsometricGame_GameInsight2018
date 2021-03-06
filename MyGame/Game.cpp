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

	Coordinate2D policemanSpawn = Coordinate2D(MAP_WIDTH_TILES - 2, 0); //for example
	NPC* policeman = new NPC();
	policeman->setPositionFromTileIsoCoords(policemanSpawn);
	policeman->setNewPath(mWorldMap.findPath({ policemanSpawn.getX(), policemanSpawn.getY() }, { MAP_LEFT_DOWN_CORNER.getX(), MAP_LEFT_DOWN_CORNER.getY() }));
	policeman->getPath().setCyclicMode(true);
	mNPCs.push_back(make_pair(policeman, policemanSpawn));

	Coordinate2D policemanSpawn2 = Coordinate2D(0, 6); //for example
	NPC* policeman2 = new NPC();
	policeman2->setPositionFromTileIsoCoords(policemanSpawn2);
	policeman2->setNewPath(mWorldMap.findPath({ policemanSpawn2.getX(), policemanSpawn2.getY() }, { MAP_RIGHT_UP_CORNER.getX(), MAP_RIGHT_UP_CORNER.getY() }));
	policeman2->getPath().setCyclicMode(true);
	mNPCs.push_back(make_pair(policeman2, policemanSpawn2));

	int gunSpawn = 4;
	Cannon* mainGun = new Cannon();
	mainGun->setType(WallType::RIGHT);
	mainGun->setExeTimeInSec(0.9);
	mainGun->setPosition(Coordinate2D(mWorld->getRightWallTileOnSpecificPositionIsoCoord(gunSpawn)));
	mCannons.push_back(make_pair(mainGun, gunSpawn));

	int gunSpawn2 = 9;
	Cannon* mainGun2 = new Cannon();
	mainGun2->setType(WallType::RIGHT);
	mainGun2->setPosition(Coordinate2D(mWorld->getRightWallTileOnSpecificPositionIsoCoord(gunSpawn)));
	mCannons.push_back(make_pair(mainGun2, gunSpawn2));
}

bool Game::isGameOver()
{
	return mIsGameOver;
}

void Game::setGameOver(bool _newState)
{
	mIsGameOver = _newState;
}
