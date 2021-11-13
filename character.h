#pragma once

#include "SDL.h"
#include "SDL_image.h"

class character
{
public:
	character();
	character(double x, double y);
	bool moveLeft;
	bool moveRight;
	bool willJump;
	void update(double deltaTime);
	void render(SDL_Renderer * renderer);
private:
	double x;
	double y;
	double w;
	double h;

	double xs;
	double ys;

	bool canJump;
	double jumpSpeed;
};