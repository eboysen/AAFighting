#pragma once
#include "SDL.h"
#include <stdio.h>
#include <iostream>
#include "SDL_image.h"
#include "environment.h"

class game
{
public:
	bool active;

	game();
	~game();
	void update();
	void render();

private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	environment* back;
};

