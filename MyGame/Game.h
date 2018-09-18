#pragma once

#include <vector>
#include <map>

#include "./Entities/MouseCursor.h"
#include "./Entities/World.h"
#include "./Entities/Player.h"
#include "./Entities/NPC.h"
#include "./Entities/Barrier.h"
#include "./Entities/Cannon.h"

class Game
{
private:

	bool mIsGameOver;

	void mUpdateAllEntityCoordinates();

public:
		
	World* mWorld;
	MouseCursor* mMouseCursor;

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
};


