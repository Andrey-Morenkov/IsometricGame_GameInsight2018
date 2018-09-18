#pragma once

#include "SDL.h"
#include "../System.h"

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

public:
	SystemGameLogic();
	virtual ~SystemGameLogic();

	void firstTimeSetup();
	void run() override;
};

