#pragma once

#include "SDL.h"
#include "SDL_image.h"

struct vector2 {
	double x;
	double y;
	vector2(double x, double y) {
		vector2::x = x;
		vector2::y = y;
	}
	vector2 normalize() {
		double len = sqrt((x * x) + (y * y));
		x /= len;
		y /= len;
		return *this;
	}
	vector2 normalize(double magnitude) {
		vector2::normalize();
		x *= magnitude;
		y *= magnitude;
		return *this;
	}
};

class character
{
public:
	character();
	character(SDL_Renderer* renderer, double x, double y);
	void update(double deltaTime);
	void attack(int leftRight, int upDown);
	vector2 attack(SDL_Rect enemyRect);
	void fixedUpdate();
	void collide(double width, double height);
	void setPlatform(double yPos);
	void render(SDL_Renderer * renderer);
	double getX() { return x; }
	double getY() { return y; }
	double getH() { return h; }
	double getW() { return w; }
	bool isFalling() { return ys > 0; }
	bool isAttacking() { return attacking; }
	void setY(double pos) { y = pos; }
	bool aimUp = false;
	bool aimDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool willJump = false;
	bool willDash = false;
	bool willAttack = false;
	bool canAttack;
private:
	SDL_Texture * texture;
	bool facingRight = true;
	double x;
	double y;
	double w;
	double h;

	double xSpeed;
	double dashXSpeed;
	double dashXDecay;
	double dashYSpeed;
	double dashYDecay;

	double ys = 0;

	double dashX = 0;
	double dashY = 0;

	bool canDash = false;
	bool canJump = false;
	double jumpSpeed;

	double attackDelay;
	double lastAttack = 0;
	bool attacking;
	SDL_Rect attackRect;
	double attackForce;
	double lastWalkTime = 0;
	double walkTimeDelay;
	int walkingIndex = 0;
	int maxWalkIndex;
};