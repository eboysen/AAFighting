#pragma once

#include "SDL.h"
#include "SDL_image.h"

class character
{
public:
	character();
	character(double x, double y);
	void update(double deltaTime);
	void fixedUpdate();
	void collide(double width, double height);
	void setPlatform(double yPos);
	void render(SDL_Renderer * renderer);
	double getX() { return x; }
	double getY() { return y; }
	double getH() { return h; }
	double getW() { return w; }
	bool isFalling() { return ys > 0; }
	void setY(double pos) { y = pos; }
	bool aimUp = false;
	bool aimDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool willJump = false;
	bool willDash = false;
	bool willAttack = false;
private:
	bool facingRight = true;
	double x;
	double y;
	double w;
	double h;

	double xSpeed;
	double dashSpeed;
	double dashDecay;

	double ys = 0;

	double dashX = 0;
	double dashY = 0;

	bool canDash = false;
	bool canJump = false;
	double jumpSpeed;
};