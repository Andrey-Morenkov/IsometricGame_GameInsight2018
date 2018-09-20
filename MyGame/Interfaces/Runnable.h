#pragma once

class Runnable
{
protected:

	double          mTimeExeInSec;
	unsigned int    mLastUpdatedTick;

public:
	Runnable() { mLastUpdatedTick = 0; mTimeExeInSec = 0; }

	void setExeTimeInSec(double _sec);
	double getExeTimeInSec();
	bool isNeedToExe();
};