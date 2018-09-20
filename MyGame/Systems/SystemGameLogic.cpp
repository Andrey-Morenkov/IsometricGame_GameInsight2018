#include<cmath>

#include "SystemGameLogic.h"
#include "../Settings.h"
#include "../SupportMacroses.h"

using namespace std;

SystemGameLogic::SystemGameLogic()
{
	mKeystate = SDL_GetKeyboardState(NULL);
	mTickrate = TICKRATE;
	mCurrentTick = SDL_GetTicks();
	mCurrentUpdateTick = mCurrentTick;
	mLastTick = 0;
	mLastUpdatedTick = 0;
	mLastStepTick = 0;
	mUpdateInputRate = UPDATE_INPUT_RATE;
}

SystemGameLogic::~SystemGameLogic()
{
}

bool SystemGameLogic::needRun()
{
	mCurrentTick = SDL_GetTicks();
	return (((mCurrentTick - mLastTick) >= (TICKS_PER_SECOND / mTickrate)) && !mGame->isGameOver());
}

bool SystemGameLogic::needUpdateInput()
{ 
	mCurrentUpdateTick = SDL_GetTicks();
	return (((mCurrentUpdateTick - mLastUpdatedTick) >= (TICKS_PER_SECOND / mUpdateInputRate)) && !mGame->isGameOver());
}

void SystemGameLogic::addOrRemoveBarrier()
{
	if (!mGame->mMouseCursor->getIsCorrect())
	{
		return;
	}

	Coordinate2D clickedTileInMapCoord = mGame->mWorld->getTileMapCoordinatesFromISOCoords(mGame->mMouseCursor->getPosition());
	Coordinate2D clickedTileInIsoCoord = mGame->mWorld->getTileISOCoordinatesFromISOCoords(mGame->mMouseCursor->getPosition());
	int pos = mGame->getBarrierPositionByMapCoord(clickedTileInMapCoord);
	
	if (pos != (int)ResultCode::NOT_EXIST)
	{
		mGame->mBarriers.erase(mGame->mBarriers.begin() + pos);
		mGame->mWorldMap.removeCollision({ clickedTileInMapCoord.getX(), clickedTileInMapCoord.getY() });
	}
	else
	{
		Barrier* newBarrier = new Barrier();
		newBarrier->setPosition(clickedTileInIsoCoord);
		auto newEntry = make_pair(newBarrier, clickedTileInMapCoord);
		mGame->mBarriers.push_back(newEntry);
		mGame->mWorldMap.addCollision({ clickedTileInMapCoord.getX(), clickedTileInMapCoord.getY() });		
	}

	refreshPath(mGame->mPlayer.first, mGame->mPlayer.second);
}

void SystemGameLogic::setPlayerDestinationToClickedTile()
{
	if (!mGame->mMouseCursor->getIsCorrect())
	{
		return;
	}

	mGame->mPlayer.first->getPath().clear();

	//correcting position to tile center of tile
	mGame->mPlayer.second = mGame->mWorld->getTileMapCoordinatesFromISOCoords(mGame->mPlayer.first->getProjectionToTileISOcoord());

	
	Coordinate2D playerMapCoord = mGame->mPlayer.second;
	Coordinate2D clickedTileInMapCoord = mGame->mWorld->getTileMapCoordinatesFromISOCoords(mGame->mMouseCursor->getPosition());

	if (playerMapCoord != clickedTileInMapCoord)
	{
		mGame->mPlayer.first->setNewPath(mGame->mWorldMap.findPath({ playerMapCoord.getX(), playerMapCoord.getY() }, { clickedTileInMapCoord.getX(), clickedTileInMapCoord.getY() }));
	}
}

void SystemGameLogic::doWholeGameStep()
{
	doPlayerStep();
	doNPCsStep();
	doFireballsStep();
	doCannonsStep();
}

void SystemGameLogic::detectColisions()
{
	checkPlayerNPCcollision();
	checkPlayerFireballCollision();
	checkPlayerTile();
}

void SystemGameLogic::checkPlayerTile()
{
	if (mGame->mPlayer.second == MAP_FINISH_POINT)
	{
		mGame->setGameOver(true);
		mGame->setExitReason(ExitReason::FINISHED);
	}
}

void SystemGameLogic::checkPlayerNPCcollision()
{
}

void SystemGameLogic::checkPlayerFireballCollision()
{
}

void SystemGameLogic::doPlayerStep()
{
	if (!mGame->mPlayer.first->isNeedToMove())
	{
		return;
	}

	Coordinate2D selfMapCoord      = mGame->mWorld->getTileMapCoordinatesFromISOCoords(mGame->mPlayer.first->getProjectionToTileISOcoord());
	Coordinate2D subtargetMapCoord = mGame->mPlayer.first->getPath().getCurrentSubDestinationMapCoordinate();

	Coordinate2D diff = selfMapCoord - subtargetMapCoord;
	//int distance = sqrt(pow((selfMapCoord.getX() - subtargetMapCoord.getX()), 2) + (pow((selfMapCoord.getY() - subtargetMapCoord.getY()), 2)));
	
	updateDirection(diff);

	mGame->mPlayer.first->setPositionFromTileIsoCoords(mGame->mWorld->getTileISOCoordinatesFromMapCoords(subtargetMapCoord));
	mGame->mPlayer.second = subtargetMapCoord;
	mGame->mPlayer.first->getPath().doStep();
}

void SystemGameLogic::doNPCsStep()
{
	for (int i = 0; i < mGame->mNPCs.size(); i++)
	{
		doSingleNPCStep(i);
	}
}

void SystemGameLogic::doSingleNPCStep(int _position)
{
	if (!mGame->mNPCs[_position].first->isNeedToMove())
	{
		return;
	}

	Coordinate2D selfMapCoord = mGame->mWorld->getTileMapCoordinatesFromISOCoords(mGame->mNPCs[_position].first->getProjectionToTileISOcoord());
	Coordinate2D subtargetMapCoord = mGame->mNPCs[_position].first->getPath().getCurrentSubDestinationMapCoordinate();

	Coordinate2D diff = selfMapCoord - subtargetMapCoord;
	//int distance = sqrt(pow((selfMapCoord.getX() - subtargetMapCoord.getX()), 2) + (pow((selfMapCoord.getY() - subtargetMapCoord.getY()), 2)));

	updateDirection(diff);

	mGame->mNPCs[_position].first->setPositionFromTileIsoCoords(mGame->mWorld->getTileISOCoordinatesFromMapCoords(subtargetMapCoord));
	mGame->mNPCs[_position].second = subtargetMapCoord;
	mGame->mNPCs[_position].first->getPath().doStep();
}

void SystemGameLogic::doFireballsStep()
{
	for (int i = 0; i < mGame->mFireballs.size(); i++)
	{
		doSingleFireballStep(i);
	}
}

void SystemGameLogic::doSingleFireballStep(int _position)
{
	if (!mGame->mFireballs[_position].first->isNeedToExe())
	{
		return;
	}

	if (mGame->mFireballs[_position].first->getPath().isFinished())
	{
		// fireball reached end of map => need delete
		mGame->mFireballs.erase(mGame->mFireballs.begin() + _position);
	}
	else
	{
		Coordinate2D subtargetMapCoord = mGame->mFireballs[_position].first->getPath().getCurrentSubDestinationMapCoordinate();
		mGame->mFireballs[_position].first->setPositionFromTileIsoCoords(mGame->mWorld->getTileISOCoordinatesFromMapCoords(subtargetMapCoord));
		mGame->mFireballs[_position].second = subtargetMapCoord;
		mGame->mFireballs[_position].first->getPath().doStep();
	}
}

void SystemGameLogic::doCannonsStep()
{
	for (int i = 0; i < mGame->mCannons.size(); i++)
	{
		doSingleCannonStep(i);
	}
}

void SystemGameLogic::doSingleCannonStep(int _position)
{
	if (!mGame->mCannons[_position].first->fire())
	{
		return;
	}

	Fireball* newFireball = new Fireball();
	
	switch (mGame->mCannons[_position].first->getType())
	{
		case WallType::RIGHT:
		{
			newFireball->setDirection(EntityDirection::DOWN_LEFT);
			Coordinate2D newFireballmapCoord = Coordinate2D(mGame->mCannons[_position].second, 0);
			newFireball->setPositionFromTileIsoCoords(mGame->mWorld->getTileISOCoordinatesFromMapCoords(newFireballmapCoord));
			newFireball->setNewPath(generateLineralPath(newFireballmapCoord, Coordinate2D(newFireballmapCoord.getX(), MAP_HEIGHT_TILES - 1)));
			mGame->mFireballs.push_back(make_pair(newFireball, newFireballmapCoord));
			break;
		}
		case WallType::LEFT:
		{
			newFireball->setDirection(EntityDirection::DOWN_RIGHT);
			Coordinate2D newFireballmapCoord = Coordinate2D(0, mGame->mCannons[_position].second);
			newFireball->setPositionFromTileIsoCoords(mGame->mWorld->getTileISOCoordinatesFromMapCoords(newFireballmapCoord));
			newFireball->setNewPath(generateLineralPath(newFireballmapCoord, Coordinate2D(MAP_WIDTH_TILES - 1, newFireballmapCoord.getX())));
			mGame->mFireballs.push_back(make_pair(newFireball, newFireballmapCoord));
			break;
		}
	}
}

void SystemGameLogic::updateDirection(Coordinate2D _difference)
{
	if (_difference.getX() > 0)
	{
		if (_difference.getY() < 0)
		{
			mGame->mPlayer.first->setDirection(EntityDirection::LEFT);
		}
		if (_difference.getY() == 0)
		{
			mGame->mPlayer.first->setDirection(EntityDirection::UP_LEFT);
		}
		if (_difference.getY() > 0)
		{
			mGame->mPlayer.first->setDirection(EntityDirection::UP);
		}
	}
	if (_difference.getX() == 0)
	{
		if (_difference.getY() < 0)
		{
			mGame->mPlayer.first->setDirection(EntityDirection::DOWN_LEFT);
		}
		if (_difference.getY() == 0)
		{
			// we are at the end of path
		}
		if (_difference.getY() > 0)
		{
			mGame->mPlayer.first->setDirection(EntityDirection::UP_RIGHT);
		}
	}
	if (_difference.getX() < 0)
	{
		if (_difference.getY() < 0)
		{
			mGame->mPlayer.first->setDirection(EntityDirection::DOWN);
		}
		if (_difference.getY() == 0)
		{
			mGame->mPlayer.first->setDirection(EntityDirection::DOWN_RIGHT);
		}
		if (_difference.getY() > 0)
		{
			mGame->mPlayer.first->setDirection(EntityDirection::RIGHT);
		}
	}
}

void SystemGameLogic::refreshPath(MoveableEntity* _who, Coordinate2D _currPos)
{
	if (_who->getPath().getRouteLength() > 0)
	{
		Coordinate2D savedDestination = _who->getPath().getPathDestinationTarget();
		_who->setNewPath(mGame->mWorldMap.findPath({ _currPos.getX(), _currPos.getY() }, { savedDestination.getX(), savedDestination.getY() }));
	}	
}

CoordinateList SystemGameLogic::generateLineralPath(Coordinate2D _startMapCoord, Coordinate2D _finishMapCoord)
{
	CoordinateList path;

	if (_startMapCoord.getX() == _finishMapCoord.getX())
	{
		if (_startMapCoord.getY() <= _finishMapCoord.getY())
		{
			int yCur = _startMapCoord.getY();
			while (yCur <= _finishMapCoord.getY())
			{
				path.push_back({ _startMapCoord.getX(), yCur});
				yCur++;
			}
		}
		else
		{
			//todo
		}
	}
	if (_startMapCoord.getY() == _finishMapCoord.getY())
	{
		if (_startMapCoord.getX() <= _finishMapCoord.getX())
		{
			int xCur = _startMapCoord.getX();
			while (xCur <= _finishMapCoord.getX())
			{
				path.push_back({ _startMapCoord.getY(), xCur });
				xCur++;
			}
		}
		else
		{
			//todo
		}
	}
	//diagonal todo

	return path;
}

void SystemGameLogic::updateCursorPosition()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	Coordinate2D newcor(x, y);
	Coordinate2D mMapPos = mGame->mWorld->getTileMapCoordinatesFromISOCoords(newcor);
	if ((mMapPos.getX() < 0) || (mMapPos.getY() < 0) || (mMapPos.getX() > (MAP_WIDTH_TILES - 1) || (mMapPos.getY() > (MAP_HEIGHT_TILES - 1))))
	{
		mGame->mMouseCursor->setIsCorrect(false);
	}
	else
	{
		mGame->mMouseCursor->setIsCorrect(true);
	}
	mGame->mMouseCursor->setPosition(mGame->mWorld->getTileISOCoordinatesFromMapCoords(mMapPos));
}

void SystemGameLogic::updateMouseEventAndQuitEvent()
{
	while (SDL_PollEvent(&mCurrentEvent) != 0)
	{
		switch (mCurrentEvent.type)
		{
			case SDL_QUIT:
			{
				mGame->setGameOver(true);
				break;
			}

			case SDL_KEYUP:
			{
				switch (mCurrentEvent.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					{
						mGame->setGameOver(true);
						break;
					}

					default:
					{
						break;
					}
				}
				break;
			}
			
			case SDL_MOUSEBUTTONDOWN:
			{
				switch (mCurrentEvent.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						//LOG_INFO("LMB pressed1");
						setPlayerDestinationToClickedTile();
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						addOrRemoveBarrier();
						break;
					}

					default:
					{
						break;
					}
				}
				break;
			}

			default:
			{
				break;
			}
		}
	}
}

void SystemGameLogic::updateKeyboardEvent()
{
	Coordinate2D newWorldPosition = mGame->mWorld->getStartingPoint();
	if (mKeystate[SDL_SCANCODE_W])
	{
		newWorldPosition.setY(newWorldPosition.getY() + WORLD_SCROLL_SPEED);
	}
	if (mKeystate[SDL_SCANCODE_A])
	{
		newWorldPosition.setX(newWorldPosition.getX() + WORLD_SCROLL_SPEED);
	}
	if (mKeystate[SDL_SCANCODE_S])
	{
		newWorldPosition.setY(newWorldPosition.getY() - WORLD_SCROLL_SPEED);
	}
	if (mKeystate[SDL_SCANCODE_D])
	{
		newWorldPosition.setX(newWorldPosition.getX() - WORLD_SCROLL_SPEED);
	}
	if (newWorldPosition != mGame->mWorld->getStartingPoint())
	{
		//something changed
		mGame->changeStartingPoint(newWorldPosition);
	}	
}

void SystemGameLogic::updateInput()
{
	if (!needUpdateInput())
	{
		return;
	}	

	updateCursorPosition();
	updateMouseEventAndQuitEvent();	
	updateKeyboardEvent();
	mLastUpdatedTick = mCurrentUpdateTick;
}

void SystemGameLogic::firstTimeSetup()
{
	mGame->setPlayerSpawnpoint(MAP_LEFT_DOWN_CORNER);

	Coordinate2D policemanSpawn = Coordinate2D(MAP_WIDTH_TILES - 2, 0); //for example
	NPC* policeman = new NPC();
	policeman->setPositionFromTileIsoCoords(policemanSpawn);
	policeman->setNewPath(mGame->mWorldMap.findPath({policemanSpawn.getX(), policemanSpawn.getY()}, {MAP_LEFT_DOWN_CORNER.getX(), MAP_LEFT_DOWN_CORNER.getY() }));
	mGame->mNPCs.push_back(make_pair(policeman, policemanSpawn));

	int gunSpawn = 4;
	Cannon* mainGun = new Cannon();
	mainGun->setType(WallType::RIGHT);
	mainGun->setPosition(Coordinate2D(mGame->mWorld->getRightWallTileOnSpecificPositionIsoCoord(gunSpawn)));
	mGame->mCannons.push_back(make_pair(mainGun, gunSpawn));
}

void SystemGameLogic::run()
{
	updateInput();
	doWholeGameStep();
	detectColisions();			
}

void SystemGameLogic::waitUntilNotPressedAnykey()
{
	bool stop = false;
	while (!stop)
	{
		while (SDL_PollEvent(&mCurrentEvent) != 0)
		{
			switch (mCurrentEvent.type)
			{
				case SDL_QUIT:
				case SDL_KEYUP:
				{
					stop = true;
				}
			}
		}
	}
}
