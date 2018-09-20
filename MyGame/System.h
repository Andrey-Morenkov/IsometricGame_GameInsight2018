#pragma once
#include "Game.h"

class System
{
protected:
	Game* mGame;

public:
	System() {};
	virtual ~System() {};

	virtual void run() = 0;
	void bindGame(Game* _game);
};