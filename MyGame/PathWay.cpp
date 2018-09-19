#include "PathWay.h"



PathWay::PathWay()
{
	mCurrStep = 0;
	mIsFinished = true;
	mIsCyclic = false;
	reverseDirection = false;
}

PathWay::PathWay(bool isCyclic) : PathWay()
{
	mIsCyclic = isCyclic;
}


PathWay::~PathWay()
{
}

int PathWay::getCurrentStep()
{
	return mCurrStep;
}

void PathWay::doStep()
{
	if (mCurrStep == (mRoute.size() - 1))
	{
		if (!mIsCyclic)
		{
			mIsFinished = true;
		}
		else
		{
			reverseDirection = true;
			mCurrStep--;
		}		
	}
	else
	{
		if (reverseDirection)
		{
			if (mCurrStep > 0)
			{
				mCurrStep--;
			}
			else
			{
				reverseDirection = false;
				mCurrStep++;
			}
		}
		else
		{
			mCurrStep++;
		}		
	}	
}

bool PathWay::isFinished()
{
	return mIsFinished;
}

Coordinate2D PathWay::getCurrentSubTargetMapCoordinate()
{
	return Coordinate2D(mRoute[mCurrStep].x, mRoute[mCurrStep].y);
}

void PathWay::setRoute(CoordinateList _newRoute)
{
	mRoute = _newRoute;
	mCurrStep = 0;
	mIsFinished = false;
}

void PathWay::clear()
{
	mRoute.clear();
	mCurrStep = 0;
	mIsFinished = false;
	reverseDirection = false;
}

void PathWay::setCyclicMode(bool iscycled)
{
	mIsCyclic = iscycled;
}
