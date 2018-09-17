#include <stdio.h>

#include "SDL.h"
#include "SDL_image.h"
#include "ResultCode.h"
#include "Initializer.h"
#include "Settings.h"
#include "SupportMacroses.h"
#include "Core.h"
#include "Entity.h"
#include "World.h"
#include "TextureWorker.h"
#include "MouseCursor.h"

using namespace std;

void render(World& _world, MouseCursor& mouset)
{
	SDL_SetRenderDrawColor(mainRenderer, 0x3b, 0x3b, 0x3b, 0x00);
	SDL_RenderClear(mainRenderer);
	_world.render();
	mouset.render();
	SDL_RenderPresent(mainRenderer);
}

#define SPEED 30

void updateInput(World& _worl, MouseCursor& mcur)
{
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	SDL_Event ev;
	while (SDL_PollEvent(&ev) != 0)
	{
		switch (ev.type)
		{
		case SDL_QUIT:
			break;

		case SDL_KEYUP:
			switch (ev.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				break;

			default:break;
			}
			break;

		default:break;
		}
	}

	Coordinate2D newPos;
	newPos = _worl.getStartingPoint();

	if (keystate[SDL_SCANCODE_W])
	{
		newPos.setY(newPos.getY() + SPEED);
		LOG_ERROR("W pressed!");
	}
	if (keystate[SDL_SCANCODE_A])
	{
		newPos.setX(newPos.getX() + SPEED);
		LOG_ERROR("A pressed!");
	}
	if (keystate[SDL_SCANCODE_S])
	{
		newPos.setY(newPos.getY() - SPEED);
		LOG_ERROR("S pressed!");
	}
	if (keystate[SDL_SCANCODE_D])
	{
		newPos.setX(newPos.getX() - SPEED);
		LOG_ERROR("D pressed!");
	}
	_worl.setStartingPoint(newPos);
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	Coordinate2D newcor(x, y);
	mcur.setPosition(newcor);
}

int main(int argc, char* args[])
{
	unsigned int currentTime, lastTime;
	lastTime = SDL_GetTicks();

	initSDLstuff(mainWindow, mainRenderer, "SDL_Game");

	World* gameWorld = new World(MAP_WIDTH_TILES, MAP_HEIGHT_TILES);
	gameWorld->setStartingPoint(Coordinate2D(100, 100));

	unsigned int lastTickrate, current, lastrendered;

	MouseCursor* mouseCur = new MouseCursor(gameWorld);
	lastTickrate = 0;
	lastrendered = 0;
	while (1)
	{
		current = SDL_GetTicks();
		if ((current - lastTickrate) >= (1000.0 / (float)TICKRATE))
		{
			updateInput(*gameWorld, *mouseCur);
			lastTickrate = current;
		}				
		if ((current - lastrendered) >= (1000.0 / (float)MAX_FPS))
		{
			render(*gameWorld, *mouseCur);
			lastrendered = current;
		}
	}

	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();

	return (int)ResultCode::SUCCESS;
}