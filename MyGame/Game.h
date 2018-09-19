#pragma once

#include <vector>
#include <map>

#include "./Entities/MouseCursor.h"
#include "./Entities/World.h"
#include "./Entities/Player.h"
#include "./Entities/NPC.h"
#include "./Entities/Barrier.h"
#include "./Entities/Cannon.h"
#include "ResultCode.h"
#include"ThirdPartyLibs/daancode_a-star/source/AStar.hpp"

enum class ExitReason
{
	QUIT,
	DEAD,
	FINISHED
};

class Game
{
private:

	bool mIsGameOver;
	ExitReason mWhyExit;
	void mUpdateAllEntityCoordinates();

public:
		
	World* mWorld;
	MouseCursor* mMouseCursor;
	AStar::Generator mWorldMap;

	//map coordinates, not iso
	pair<Player*, Coordinate2D>           mPlayer;
	vector<pair<NPC*, Coordinate2D> >     mNPCs;
	vector<pair<Barrier*, Coordinate2D> > mBarriers;
	vector<pair<Cannon*, Coordinate2D> >  mCannons;
	//Fireball todo

	Game();
	~Game();

	void createNewGame();
	bool isGameOver();
	void setGameOver(bool _newState);
	void setPlayerSpawnpoint(Coordinate2D _spawnpointMapCoods); //only for setup state
	void changeStartingPoint(Coordinate2D _newStartingPoint);
	
	int getBarrierPositionByMapCoord(Coordinate2D _possibleBarrierMapCoords);

	ExitReason getExitReason();
	void setExitReason(ExitReason _reason);
};

