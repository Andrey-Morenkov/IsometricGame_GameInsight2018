#pragma once
#include "./Interfaces/Runnable.h"
#include "Game.h"

class System : public Runnable
{
protected:
	Game* mGame;

public:
	System() {};
	virtual ~System() {};

	void run() override = 0;
	void bindGame(Game* _game);
};