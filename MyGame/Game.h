#pragma once

#include <vector>

#include "SystemUpdateInput.h"
#include "MouseCursor.h"
#include "World.h"
#include "Player.h"
#include "NPC.h"
#include "Barrier.h"
#include "Cannon.h"



class Game
{
private:
	World* mWorld;
	MouseCursor* mMouseCursor;
	Player* mPlayer;
				
	vector<NPC*> mNPCs;
	vector<Barrier*> mBarriers;
	vector<Cannon*> mCannons;

public:

	Game();
	~Game();
};


