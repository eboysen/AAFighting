#pragma once
#include <stdio.h>
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "character.h"

class game
{
public:
	bool active;
	game(Uint16 width, Uint16 height);
	~game();
	void update();
	void render();

private:
	void handleInput(SDL_Event& event, bool keyDown);
	SDL_Window * window;
	SDL_Renderer * renderer;
	Uint16 window_width;
	Uint16 window_height;
	Uint64 now;
	Uint64 last;
	character player;
};

