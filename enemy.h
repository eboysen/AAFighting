#pragma once

#include "SDL.h"
#include "SDL_image.h"

class enemy
{
public:
	enemy();
	enemy(double x, double y);
	void update(double deltaTime);
	void collide(double width, double height);
	void render(SDL_Renderer* renderer);
	bool willJump;
private:
	double x;
	double y;
	double w;
	double h;

	double moveX;
	double xs;
	double ys;

	bool canJump;
	double jumpSpeed;
};

