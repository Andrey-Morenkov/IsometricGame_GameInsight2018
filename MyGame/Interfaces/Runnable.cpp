#include "Runnable.h"
#include "SDL.h"
#include "../Settings.h"

void Runnable::setExeTimeInSec(double _sec)
{
	mTimeExeInSec = _sec;
}

double Runnable::getExeTimeInSec()
{
	return mTimeExeInSec;
}

bool Runnable::isNeedToExe()
{
	unsigned int currTick = SDL_GetTicks();
	if (((double)(currTick - mLastUpdatedTick) / TICKS_PER_SECOND) < mTimeExeInSec)
	{
		return false;
	}
	mLastUpdatedTick = currTick;
	return true;
}
