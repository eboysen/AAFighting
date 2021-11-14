#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "entityRenderer.h"
#include "entitySet.h"
#include "vector2.h"

class entity
{
public:
	enum EntityInput {
		Up,
		Down,
		Left,
		Right,
		Jump,
		Dash,
		Attack,
		Special
	};

	// Constructors
	entity();
	entity(SDL_Renderer* renderer, entitySet set, double x, double y);

	// Generic
	void input(EntityInput input, bool active);
	void update(double deltaTime);
	void fixedUpdate();
	void collide(double width, double height);
	void render(SDL_Renderer* renderer);

	// Special
	void handleJump();
	void handleDash(int leftRight, int upDown);
	void handleAttack(int leftRight, int upDown);
	vector2 attack(SDL_Rect enemyRect);
	void setPlatform(double y);
	void applyKickback(double x, double y);

	// Properties
	SDL_Rect getHitbox() { return renderer.getEntityRect(xPos, yPos); }
	double getX() { return xPos; }
	double getY() { return yPos; }
	double getH() { return renderer.getHeight(); }
	double getW() { return renderer.getWidth(); }
	bool isFalling() { return yVel > 0; }
	bool isAttacking() { return attacking; }

private:
	// Base
	entityRenderer renderer;
	bool facingRight = true;

	// X and Y Position (Bottom-Left Corner)
	double xPos;
	double yPos;
	double xVel = 0;
	double yVel = 0;
	double xMoveSpeed;

	// Looking Direction
	bool aimUp = false;
	bool aimDown = false;
	bool aimLeft = false;
	bool aimRight = false;

	// Jumping
	bool canJump = false;
	double jumpForce;

	// Dashing
	bool canDash = false;
	double xDash = 0;
	double xDashSpeed;
	double xDashDecay;
	double yDash = 0;
	double yDashSpeed;
	double yDashDecay;

	// Attacking
	double attackDelay;
	double lastAttack = 0;
	bool attacking;
	SDL_Rect attackRect;
	double attackForce;
	bool willJump = false;
	bool willDash = false;
	bool willAttack = false;
	bool canAttack;
};