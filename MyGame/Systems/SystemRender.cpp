#include "SystemRender.h"
#include "../Core.h"
#include "../Settings.h"

using namespace std;

bool SystemRender::needRender()
{
	mCurrentRenderingTick = SDL_GetTicks();
	return (((mCurrentRenderingTick - mLastRenderedTick) >= (TICKS_IN_SECOND / mMaxFPS)) && !mGame->isGameOver());
}

SystemRender::SystemRender()
{
	mCurrentRenderingTick = SDL_GetTicks();
	mLastRenderedTick = 0;
	mMaxFPS = MAX_FPS;
}

SystemRender::~SystemRender()
{
}

void SystemRender::run()
{
	if (!needRender())
	{
		return;
	}

	SDL_SetRenderDrawColor(mainRenderer, 0x3b, 0x3b, 0x3b, 0x00);
	SDL_RenderClear(mainRenderer);

	mGame->mWorld->render();
	if (mGame->mMouseCursor->getPosition().getY() >= mGame->mWorld->getStartingPoint().getY())
	{
		mGame->mMouseCursor->render();
	}	
	mGame->mPlayer.first->render();

	for (int i = 0; i < mGame->mNPCs.size(); i++)
	{
		mGame->mNPCs[i].first->render();
	}
	for (int i = 0; i < mGame->mBarriers.size(); i++)
	{
		mGame->mBarriers[i].first->render();
	}
	for (int i = 0; i < mGame->mCannons.size(); i++)
	{
		mGame->mCannons[i].first->render();
	}

	SDL_RenderPresent(mainRenderer);
	mLastRenderedTick = mCurrentRenderingTick;
}
