#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "character.h"
#include "TextureManager.h"
class environment
{
public:
	environment();
	~environment();
	void renderEnvironment(SDL_Renderer * render, int width, int height);
	void platformCheck(character* Character);
	void characterCollided(character* Character, double yPos);

};

