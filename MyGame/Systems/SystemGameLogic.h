#pragma once

#include "SDL.h"
#include "../System.h"
#include "../ThirdPartyLibs/daancode_a-star/source/AStar.hpp"

class SystemGameLogic :	public System
{
private:

	int          mUpdateInputRate;
	int          mTickrate;
	unsigned int mCurrentUpdateTick;
	unsigned int mCurrentTick;
	unsigned int mLastTick;
	unsigned int mLastUpdatedTick;
	SDL_Event    mCurrentEvent;
	const Uint8* mKeystate;
	AStar::CoordinateList mPlayerPath;
	int mPlayerCurrentStep;

	void updateCursorPosition();
	void updateMouseEventAndQuitEvent();
	void updateKeyboardEvent();
	void updateInput();
	void doPlayerStep();
	bool needRun();
	bool needUpdateInput();

	void addOrRemoveBarrier();
	void setPlayerDestination();

public:
	SystemGameLogic();
	virtual ~SystemGameLogic();

	void firstTimeSetup();
	void run() override;
};

