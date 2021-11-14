#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "entity.h"
class environment
{
public:
	environment();
	environment(SDL_Renderer* render);
	~environment();
	void renderEnvironment(SDL_Renderer * render, int width, int height);
	void platformCheck(entity* Entity);
	void entityCollided(entity* Entity, double yPos);
	void setLevel(int select);
	int level;
};

