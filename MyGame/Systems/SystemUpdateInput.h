#pragma once

#include "../Game.h"
#include "../System.h"

class SystemUpdateInput : public System 
{
public:
	SystemUpdateInput() = delete;
	SystemUpdateInput(Game* _game);
	~SystemUpdateInput();

	void run() override;
};

