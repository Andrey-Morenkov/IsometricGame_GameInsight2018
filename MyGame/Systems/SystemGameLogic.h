#pragma once

#include "SDL.h"
#include "../System.h"
#include "../ThirdPartyLibs/daancode_a-star/source/AStar.hpp"
#include "../MoveableEntity.h"

class SystemGameLogic :	public System
{
private:

	int          mUpdateInputRate;
	int          mTickrate;
	unsigned int mCurrentUpdateTick;
	unsigned int mCurrentTick;
	unsigned int mLastTick;
	unsigned int mLastUpdatedTick;
	unsigned int mCurrentStepTick;
	unsigned int mLastStepTick;
	SDL_Event    mCurrentEvent;
	const Uint8* mKeystate;

	void updateCursorPosition();
	void updateMouseEventAndQuitEvent();
	void updateKeyboardEvent();
	void updateInput();
	bool needRun();
	bool needUpdateInput();

	void addOrRemoveBarrier();
	void setPlayerDestinationToClickedTile();

	void doWholeGameStep();
	void detectColisions();
	void checkPlayerTile();
	void checkPlayerNPCcollision();
	void checkPlayerFireballCollision();
	
	void doPlayerStep();
	void doNPCsStep();
	void doSingleNPCStep(int _position);
	void doFireballsStep();
	void doSingleFireballStep(int _position);
	void doCannonsStep();
	void doSingleCannonStep(int _position);

	void updateDirection(MoveableEntity* _who, Coordinate2D _difference);
	void refreshPath(MoveableEntity* _who, Coordinate2D _currPos);
	CoordinateList generateLineralPath(Coordinate2D _startMapCoord, Coordinate2D _finishMapCoord);
public:
	SystemGameLogic();
	virtual ~SystemGameLogic();

	void firstTimeSetup();
	void run() override;
	void waitUntilNotPressedAnykey();
};

