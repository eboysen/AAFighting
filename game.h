#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "environment.h"
#include "rain.h"
#include "entitySet.h"
#include "entity.h"
#include "enemyBrain.h"

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
	Uint64 last = 0;
	double currentTime = 0;
	environment environment;
	entity player;
	entity enemy;
	enemyBrain enemyBrain;
	std::vector<rain> weather;
};

