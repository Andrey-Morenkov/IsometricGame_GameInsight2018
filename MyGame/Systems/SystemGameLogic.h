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

	void updateCursorPosition();
	void updateMouseEventAndQuitEvent();
	void updateKeyboardEvent();
	void updateInput();
	bool needRun();
	bool needUpdateInput();

	void addOrRemoveBarrier();
	void setPlayerDestination();

	void doWholeGameStep();
	void detectColisions();
	void doPlayerStep();
	void doNPCsStep();
	void doFireballsStep();

	void updateDirectionAndMove(Coordinate2D _difference, int _dist);
public:
	SystemGameLogic();
	virtual ~SystemGameLogic();

	void firstTimeSetup();
	void run() override;
	void waitUntilNotPressedAnykey();
};

