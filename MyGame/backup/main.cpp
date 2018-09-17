#include <stdio.h>

#include "SDL.h"
#include "SDL_image.h"
#include "ResultCode.h"
#include "Initializer.h"
#include "Settings.h"
#include "SupportMacroses.h"
#include "Core.h"

using namespace std;

void render()
{
	SDL_SetRenderDrawColor(mainRenderer, 0x3b, 0x3b, 0x3b, 0x00);
	SDL_RenderClear(mainRenderer);
	Game::Instance().generateWorld();
	SDL_RenderPresent(mainRenderer);
}

void updateInput()
{
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&Game::Instance().getEvent()) != 0)
	{
		switch (Game::Instance().getEvent().type)
		{
		case SDL_QUIT:
			Game::Instance().setIsGameOver(true);
			break;

		case SDL_KEYUP:
			switch (Game::Instance().getEvent().key.keysym.sym)
			{
			case SDLK_ESCAPE:
				Game::Instance().setIsGameOver(true);
				break;

			default:break;
			}
			break;

		default:break;
		}
	}


	if (keystate[SDL_SCANCODE_W])
	{
		Game::Instance().getIsometricEngine()->setScrollY(Game::Instance().getIsometricEngine()->getScrollY() + Game::Instance().getMapScrollSpeed());
		Game::Instance().getIsometricEngine()->setScrollX(Game::Instance().getIsometricEngine()->getScrollX() + Game::Instance().getMapScrollSpeed());

	}
	if (keystate[SDL_SCANCODE_A])
	{

	}
	if (keystate[SDL_SCANCODE_S])
	{


	}
	if (keystate[SDL_SCANCODE_D])
	{

	}
}

int main(int argc, char* args[])
{
	initSDLstuff(mainWindow, mainRenderer, "SDL_Game");
	initGame();

	unsigned int currentTime, lastTime;
	lastTime = SDL_GetTicks();

	while (!Game::Instance().getIsGameOver())
	{
		updateInput();

		currentTime = SDL_GetTicks();
		if (currentTime - lastTime >= (1000.0 / (float)MAX_FPS))
		{
			render();
			lastTime = currentTime;
		}
	}
	
	

	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();

	return (int)ResultCode::SUCCESS;
}