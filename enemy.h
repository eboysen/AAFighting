#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "character.h"

class enemy
{
public:
	enemy();
	enemy(double x, double y);
	void think(character* player);
	void update(double deltaTime);
	void collide(double width, double height);
	void render(SDL_Renderer* renderer);
	bool willJump;
private:
	double x;
	double y;
	double w;
	double h;

	double ys;

	bool canJump;
	double jumpSpeed;
};

