#include <stdio.h>

#include "Initializer.h"
#include "Core.h"
#include "Game.h"
#include "Systems/SystemGameLogic.h"
#include "Systems/SystemRender.h"
#include "TextureWorker.h"

int main(int argc, char* args[])
{
	initSDLstuff(mainWindow, mainRenderer, "SDL_Game");

	Game isoGame;
	isoGame.createNewGame();	
	SystemRender renderer;
	renderer.bindGame(&isoGame);
	SystemGameLogic logic;
	logic.bindGame(&isoGame);	
	logic.firstTimeSetup();

	while (!isoGame.isGameOver())
	{
		logic.run();
		renderer.run();
	}

	switch (isoGame.getExitReason())
	{
		case ExitReason::FINISHED:
		{
			renderer.renderSuccessfulScreen();
			logic.waitUntilNotPressedAnykey();
			break;
		}

		case ExitReason::DEAD:
		{
			renderer.renderDeadScreen();
			logic.waitUntilNotPressedAnykey();
			break;
		}

		default:
			break;
	}

	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();

	return (int)ResultCode::SUCCESS;
}