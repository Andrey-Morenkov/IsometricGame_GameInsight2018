#include "SystemUpdateInput.h"
#include "../SupportMacroses.h"
#include "SDL.h"

SystemUpdateInput::SystemUpdateInput(Game* _game)
{
	POINTER_VALIDATION(_game);
	mGame = _game;
}

SystemUpdateInput::~SystemUpdateInput()
{
}

void SystemUpdateInput::run()
{

}
