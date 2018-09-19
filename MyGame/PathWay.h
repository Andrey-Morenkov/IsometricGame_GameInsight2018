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
	void doStep();
	bool isFinished();
	Coordinate2D getCurrentSubTargetMapCoordinate();
	void setRoute(CoordinateList _newRoute);
	void clear();
	void setCyclicMode(bool iscycled);
};

