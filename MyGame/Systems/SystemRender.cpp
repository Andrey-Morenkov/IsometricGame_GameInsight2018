#include "SystemRender.h"
#include "../Core.h"
#include "../Settings.h"
#include "../TextureWorker.h"

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
	if (!needRender() && !mGame->isGameOver())
	{
		return;
	}

	SDL_SetRenderDrawColor(mainRenderer, 0x3b, 0x3b, 0x3b, 0x00);
	SDL_RenderClear(mainRenderer);

	mGame->mWorld->render();
	for (int i = 0; i < mGame->mBarriers.size(); i++)
	{
		mGame->mBarriers[i].first->render();
	}
	if (mGame->mMouseCursor->getIsCorrect())
	{
		mGame->mMouseCursor->render();
	}	
	mGame->mPlayer.first->render();

	for (int i = 0; i < mGame->mNPCs.size(); i++)
	{
		mGame->mNPCs[i].first->render();
	}
	for (int i = 0; i < mGame->mCannons.size(); i++)
	{
		mGame->mCannons[i].first->render();
	}

	SDL_RenderPresent(mainRenderer);
	mLastRenderedTick = mCurrentRenderingTick;
}

void SystemRender::renderSuccessfulScreen()
{
	Texture successfulScreen(SUCCESSFUL_SCREEN_WIDTH_IN_PIXELS, SUCCESSFUL_SCREEN_HIIGHT_IN_PIXELS);
	successfulScreen.loadFromPath(SUCCESSFUL_SCREEN_TEXTURE_PATH);
	TextureWorker::renderTextureRegion(successfulScreen, Coordinate2D((MAIN_WINDOW_WIDTH / 2 - SUCCESSFUL_SCREEN_WIDTH_IN_PIXELS / 2), (MAIN_WINDOW_HEIGHT / 2 - SUCCESSFUL_SCREEN_HIIGHT_IN_PIXELS / 2)), nullptr);
	SDL_RenderPresent(mainRenderer);
}

void SystemRender::renderDeadScreen()
{
	Texture deadScreen(DEAD_SCREEN_WIDTH_IN_PIXELS, DEAD_SCREEN_HIIGHT_IN_PIXELS);
	deadScreen.loadFromPath(DEAD_SCREEN_TEXTURE_PATH);
	TextureWorker::renderTextureRegion(deadScreen, Coordinate2D((MAIN_WINDOW_WIDTH / 2 - DEAD_SCREEN_WIDTH_IN_PIXELS / 2), (MAIN_WINDOW_HEIGHT / 2 - DEAD_SCREEN_HIIGHT_IN_PIXELS / 2)), nullptr);
	SDL_RenderPresent(mainRenderer);
}
