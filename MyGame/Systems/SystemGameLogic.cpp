#include "SystemGameLogic.h"
#include "../Settings.h"
#include "../SupportMacroses.h"

SystemGameLogic::SystemGameLogic()
{
	mKeystate = SDL_GetKeyboardState(NULL);
	mTickrate = TICKRATE;
	mCurrentTick = SDL_GetTicks();
	mCurrentUpdateTick = mCurrentTick;
	mLastTick = 0;
	mLastUpdatedTick = 0;
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

void SystemGameLogic::updateCursorPosition()
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	Coordinate2D newcor(x, y);
	mGame->mMouseCursor->setPosition(mGame->mWorld->getTileISOCoordinatesFromISOCoords(newcor));
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
						//TODO
						break;
					}

					case SDL_BUTTON_RIGHT:
					{
						//TODO
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
	mGame->changeStartingPoint(newWorldPosition);
}

void SystemGameLogic::updateInput()
{
	updateMouseEventAndQuitEvent();
	updateCursorPosition();
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
		
}
