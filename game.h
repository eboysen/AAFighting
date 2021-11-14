#pragma once
#include <stdio.h>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "environment.h"
#include "character.h"
#include "enemy.h"

class game
{
public:
	bool active;
	game(Uint16 width, Uint16 height);
	~game();
	void update();
	void render();

private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	Uint16 window_width;
	Uint16 window_height;
	Uint64 now;
	Uint64 last;
	environment* back;
	character player;
	enemy enemy;
};

