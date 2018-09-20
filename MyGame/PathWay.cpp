#include "PathWay.h"



PathWay::PathWay()
{
	clear();
	mIsCyclic = false;
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

int PathWay::getRouteLength()
{
	return mRoute.size();
}

void PathWay::doStep()
{
	if (mCurrStep == (mRoute.size() - 1))
	{
		if (!mIsCyclic)
		{
			clear(); //finished!
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

bool PathWay::isCyclic()
{
	return mIsCyclic;
}

bool PathWay::isReverse()
{
	return reverseDirection;
}

Coordinate2D PathWay::getCurrentSubDestinationMapCoordinate()
{
	return Coordinate2D(mRoute[mCurrStep].x, mRoute[mCurrStep].y);
}

Coordinate2D PathWay::getPathDestinationTarget()
{
	return Coordinate2D(mRoute[mRoute.size() - 1].x, mRoute[mRoute.size() - 1].y);
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
	mIsFinished = true;
	reverseDirection = false;
}

void PathWay::setCyclicMode(bool iscycled)
{
	mIsCyclic = iscycled;
}
