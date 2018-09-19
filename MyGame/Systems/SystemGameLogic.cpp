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
	return (((mCurrentTick - mLastTick) >= (TICKS_IN_SECOND / mTickrate)) && !mGame->isGameOver());
}

bool SystemGameLogic::needUpdateInput()
{ 
	mCurrentUpdateTick = SDL_GetTicks();
	return (((mCurrentUpdateTick - mLastUpdatedTick) >= (TICKS_IN_SECOND / mUpdateInputRate)) && !mGame->isGameOver());
}

void SystemGameLogic::addOrRemoveBarrier()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);

	Coordinate2D clickedTileInMapCoord = mGame->mWorld->getTileMapCoordinatesFromISOCoords(Coordinate2D(x, y));
	Coordinate2D clickedTileInIsoCoord = mGame->mWorld->getTileISOCoordinatesFromISOCoords(Coordinate2D(x, y));
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
}

void SystemGameLogic::setPlayerDestination()
{
	mGame->mPlayer.first->getPath().clear();

	//correct position to tile center of tile
	//mGame->mPlayer.first->setPositionFromTileIsoCoords(mGame->mWorld->getTileISOCoordinatesFromISOCoords(mGame->mPlayer.first->getPosition()));
	mGame->mPlayer.second = mGame->mWorld->getTileMapCoordinatesFromISOCoords(mGame->mPlayer.first->getProjectionToTileISOcoord());

	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	Coordinate2D playerMapCoord = mGame->mPlayer.second;
	Coordinate2D clickedTileInMapCoord = mGame->mWorld->getTileMapCoordinatesFromISOCoords(Coordinate2D(x, y));

	if (playerMapCoord != clickedTileInMapCoord)
	{
		mGame->mPlayer.first->setNewPath(mGame->mWorldMap.findPath({ playerMapCoord.getX(), playerMapCoord.getY() }, { clickedTileInMapCoord.getX(), clickedTileInMapCoord.getY() }));
	}
}

void SystemGameLogic::doWholeGameStep()
{
	if (!mGame->mPlayer.first->getPath().isFinished())
	{
		doPlayerStep();
	}
	doNPCsStep();
	doFireballsStep();
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
	unsigned int currTick = SDL_GetTicks();
	if (((double)(currTick - mGame->mPlayer.first->mLastUpdatedTick) / TICKS_IN_SECOND) < mGame->mPlayer.first->getTimeForStepInSec())
	{
		return;
	}
	mGame->mPlayer.first->mLastUpdatedTick = currTick;

	Coordinate2D selfMapCoord = mGame->mWorld->getTileMapCoordinatesFromISOCoords(mGame->mPlayer.first->getProjectionToTileISOcoord());
	Coordinate2D subtargetMapCoord = mGame->mPlayer.first->getPath().getCurrentSubTargetMapCoordinate();

	Coordinate2D diff = selfMapCoord - subtargetMapCoord;
	//int distance = sqrt(pow((selfMapCoord.getX() - subtargetMapCoord.getX()), 2) + (pow((selfMapCoord.getY() - subtargetMapCoord.getY()), 2)));
	
	updateDirection(diff);

	mGame->mPlayer.first->setPositionFromTileIsoCoords(mGame->mWorld->getTileISOCoordinatesFromMapCoords(subtargetMapCoord));
	mGame->mPlayer.second = subtargetMapCoord;
	mGame->mPlayer.first->getPath().doStep();
}

void SystemGameLogic::doNPCsStep()
{
	//for (int i = 0; i < mGame->mNPCs.size(); i++)
	//{
	//	if (((double)(mCurrentStepTick - mLastStepTick) / TICKS_IN_SECOND) < mGame->mNPCs[i].first->getTimeForStepInSec())
   //	{
//			continue;
//		}

		
//	}
	

}

void SystemGameLogic::doFireballsStep()
{
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
			mGame->mPlayer.first->setDirection(EntityDirection::RIGHT_DOWN);
		}
		if (_difference.getY() > 0)
		{
			mGame->mPlayer.first->setDirection(EntityDirection::RIGHT);
		}
	}
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
						LOG_INFO("ЛКМ pressed1");
						setPlayerDestination();
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
	updateCursorPosition();
	updateMouseEventAndQuitEvent();	
	updateKeyboardEvent();
}

void SystemGameLogic::firstTimeSetup()
{
	mGame->setPlayerSpawnpoint(MAP_LEFT_DOWN_CORNER);
}

void SystemGameLogic::run()
{
	if (needUpdateInput())
	{
		updateInput();
		mLastUpdatedTick = mCurrentUpdateTick;
	}
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
