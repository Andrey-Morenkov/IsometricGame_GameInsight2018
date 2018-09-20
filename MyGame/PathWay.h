#pragma once
#include "ThirdPartyLibs/daancode_a-star/source/AStar.hpp"
#include "Coordinate2D.h"

using namespace AStar;

class PathWay
{
private:
	CoordinateList mRoute;
	int mCurrStep;
	bool mIsFinished;
	bool mIsCyclic;
	bool reverseDirection;

public:
	PathWay();
	PathWay(bool isCyclic);
	~PathWay();

	int getCurrentStep();
	int getRouteLength();
	void doStep();

	bool isFinished();
	bool isCyclic();
	bool isReverse();

	Coordinate2D getCurrentSubDestinationMapCoordinate();
	Coordinate2D getPathDestinationTarget();
	
	void setRoute(CoordinateList _newRoute);
	void clear();
	void setCyclicMode(bool iscycled);
};

