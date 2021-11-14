#include "entity.h"
#include <iostream>

const double GRAVITY = 1.4;

// Constructors
entity::entity() {
	entity(nullptr, entitySet(), 0, 0);
}
entity::entity(SDL_Renderer* renderer, entitySet set, double x, double y) {
	entity::renderer = entityRenderer(renderer, set);
	entity::xPos = x - 40;
	entity::yPos = y;
	entity::xMoveSpeed = 10;
	entity::xDashSpeed = 42;
	entity::xDashDecay = 0.6;
	entity::yDashSpeed = 36;
	entity::yDashDecay = 0.9;
	entity::jumpForce = 20;
	entity::canAttack = true;
	entity::attackRect = SDL_Rect();
	entity::attacking = false;
	entity::attackDelay = 0.1;
	entity::attackForce = 20;
	entity::health = 100;
}

// Generic
void entity::input(EntityInput input, bool active) {
	if (locked) return;
	switch (input) {
	case EntityInput::Up:
		aimUp = active;
		break;
	case EntityInput::Down:
		aimDown = active;
		renderer.crouch = active;
		break;
	case EntityInput::Left:
		aimLeft = active;
		break;
	case EntityInput::Right:
		aimRight = active;
		break;
	case EntityInput::Jump:
		willJump = active;
		break;
	case EntityInput::Dash:
		willDash = active;
		break;
	case EntityInput::Attack:
		willAttack = active;
		if (!active) {
			canAttack = true;
		}
		break;
	case EntityInput::Special:
		break;
	}
}
void entity::update(double deltaTime) {
	renderer.handleMovement(deltaTime, xVel);

	lastAttack += deltaTime;
	if (willAttack && lastAttack >= attackDelay && canAttack) {
		int leftRight = (aimLeft ? -1 : 0) + (aimRight ? 1 : 0);
		int upDown = (aimUp ? -1 : 0) + (aimDown ? 1 : 0);
		entity::handleAttack(leftRight, upDown);
		lastAttack = 0;
		canAttack = false;
	}
}
void entity::fixedUpdate() {
	int leftRightInput = (aimLeft ? -1 : 0) + (aimRight ? 1 : 0);
	int upDownInput = (aimUp ? -1 : 0) + (aimDown ? 1 : 0);
	if (leftRightInput > 0) {
		facingRight = true;
	}
	else if (leftRightInput < 0) {
		facingRight = false;
	}
	xPos += xMoveSpeed * leftRightInput;
	if (xVel > 0.01 || xVel < 0.01) {
		xPos += xVel;
		xVel /= 2;
	}
	yVel += GRAVITY;
	yPos += yVel;
	if (willDash && canDash) {
		entity::handleDash(leftRightInput, upDownInput);
	}
	if (willJump && canJump) {
		entity::handleJump();
	}
	if (xDash > 0.01 || xDash < 0.01) {
		xPos += xDash;
		xDash *= xDashDecay;
	}
	if (yDash > 0.01 || yDash < 0.01) {
		yPos += yDash;
		yDash *= yDashDecay;
	}
}
void entity::collide(double width, double height) {
	canJump = false;

	if (yPos > height) {
		setPlatform(height);
	}
	if (xPos < 0) {
		xPos = 0;
	}
	if (xPos > width - renderer.getWidth()) {
		xPos = width - renderer.getWidth();
	}
}
void entity::render(SDL_Renderer* renderer) {
	if (!alive) return;
	entity::renderer.render(renderer, facingRight, xPos, yPos);

	if (lastAttack < attackDelay - 0.01) {
		SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &attackRect);
		attacking = false;
	}
}

// Special
void entity::handleJump() {
	yVel = -jumpForce;
	willJump = false;
}
void entity::handleDash(int leftRight, int upDown) {
	xDash = leftRight * xDashSpeed;
	yDash = upDown * yDashSpeed;
	if (xDash == 0 && yDash == 0) {
		xDash = (facingRight ? 1 : -1) * xDashSpeed;
	}
	if (yVel > 0) {
		yVel = 0;
	}
	willDash = false;
	canDash = false;
}
void entity::handleAttack(int leftRight, int upDown) {
	int attackSize = 50;
	if (leftRight > 0) {
		attackRect.x = xPos + renderer.getWidth();
		attackRect.w = attackSize * 2;
	}
	else if (leftRight < 0) {
		attackRect.x = xPos - attackSize * 2;
		attackRect.w = attackSize * 2;
	}
	else {
		if (facingRight) {
			attackRect.x = xPos + renderer.getWidth() - attackSize * 1.5;
			attackRect.w = attackSize * 2;
		}
		else {
			attackRect.x = xPos - attackSize * 0.5;
			attackRect.w = attackSize * 2;
		}
	}
	if (upDown < 0) {
		attackRect.y = yPos - renderer.getHeight() - attackSize * 0.5;
		attackRect.h = attackSize;
		if (facingRight) {
			attackRect.x += attackSize * 0.75;
		}
		else {
			attackRect.x -= attackSize * 0.75;
		}
	}
	else if (upDown > 0) {
		attackRect.y = yPos - attackSize;
		attackRect.h = attackSize;
		if (facingRight) {
			attackRect.x += attackSize * 0.75;
			attackRect.w *= 1.25;
		}
		else {
			attackRect.x -= attackSize * 0.75;
			attackRect.w *= 1.25;
		}
	}
	else {
		attackRect.y = yPos - renderer.getHeight() / 2 - attackSize;
		attackRect.h = attackSize * 2;
	}
	attacking = true;
}
vector2 entity::attack(SDL_Rect enemyRect) {
	bool hit = SDL_HasIntersection(&attackRect, &enemyRect);
	if (hit) {
		double xDir = xPos + renderer.getWidth() * 0.5 - (enemyRect.x + enemyRect.w * 0.5);
		double yDir = attackRect.y + attackRect.h * 0.5 - (enemyRect.y + enemyRect.h * 0.5);
		return vector2(-xDir, -yDir).normalize(attackForce);
	}
	return vector2(0, 0);
}
void entity::setPlatform(double y) {
	yPos = y;
	yVel = 0;
	canJump = true;
	canDash = true;
}
void entity::applyKickback(double x, double y) {
	xVel += x;
	yVel += y;
	damage(1 + rand()%3);
}
void entity::damage(int amount) {
	health -= amount;
}
void entity::lock() {
	input(Left, false);
	input(Right, false);
	input(Up, false);
	input(Down, false);
	input(Dash, false);
	input(Jump, false);
	input(Attack, false);
	locked = true;
}
void entity::kill() {
	lock();
	alive = false;
}