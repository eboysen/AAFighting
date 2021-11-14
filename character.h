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
	void collide(double width, double height);
	void setPlatform(double yPos);
	void render(SDL_Renderer * renderer);
	double getX() { return x; }
	double getY() { return y; }
	double getH() { return h; }
	double getW() { return w; }
	bool isFalling() { return ys > 0; }
	void setY(double pos) { y = pos; }
private:
	double x;
	double y;
	double w;
	double h;

	double moveX;
	double ys;

	bool canJump;
	double jumpSpeed;
};