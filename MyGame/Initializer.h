#pragma once
#include <string>
#include <stdlib.h>

#include "SDL.h"
#include "ResultCode.h"
#include "Game.h"

using namespace std;

void initSDLstuff(SDL_Window*& _window, SDL_Renderer*& _renderer, string _windowName = "SampleWindow");