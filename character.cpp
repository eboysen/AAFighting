#include "character.h"
#include <iostream>
#include "TextureManager.h"

const float GRAVITY = 1.4;

character::character() {
}

character::character(SDL_Renderer* renderer, double x, double y) {
	character::texture = TextureManager::loadTexture("leftCloud.png", renderer);
	std::cout << texture << std::endl;
	std::cout << SDL_QueryTexture(texture, NULL, NULL, 0, 0) << std::endl;
	character::x = x - 40;
	character::y = y;
	character::w = 80;
	character::h = 160;
	character::xSpeed = 10;
	character::dashXSpeed = 42;
	character::dashXDecay = 0.6;
	character::dashYSpeed = 36;
	character::dashYDecay = 0.9;
	character::jumpSpeed = 20;
	character::canAttack = true;
	character::attackRect = SDL_Rect();
	character::attacking = false;
	character::attackDelay = 0.1;
	character::attackForce = 20;
}

void character::update(double deltaTime) {
	lastAttack += deltaTime;
	if (willAttack && lastAttack >= attackDelay && canAttack) {
		int leftRight = (moveLeft ? -1 : 0) + (moveRight ? 1 : 0);
		int upDown = (aimUp ? -1 : 0) + (aimDown ? 1 : 0);
		if (leftRight == 0 && upDown == 0) {
			leftRight = facingRight ? 1 : -1;
		}
		character::attack(leftRight, upDown);
		lastAttack = 0;
		canAttack = false;
	}
}

void character::attack(int leftRight, int upDown) {
	int attackSize = 50;
	if (leftRight > 0) {
		attackRect.x = x + w + attackSize * 0.5;
		attackRect.w = attackSize;
	}
	else if (leftRight < 0) {
		attackRect.x = x - attackSize * 1.5;
		attackRect.w = attackSize;
	}
	else {
		if (facingRight) {
			attackRect.x = x + w - attackSize;
			attackRect.w = attackSize * 2;
		}
		else {
			attackRect.x = x - attackSize;
			attackRect.w = attackSize * 2;
		}
	}
	if (upDown < 0) {
		attackRect.y = y - h - attackSize * 0.5;
		attackRect.h = attackSize;
	}
	else if (upDown > 0) {
		attackRect.y = y - attackSize;
		attackRect.h = attackSize;
		if (facingRight) {
			attackRect.x += attackSize * 1.25;
		}
		else {
			attackRect.x -= attackSize * 1.25;
		}
	}
	else {
		attackRect.y = y - h / 2 - attackSize * 0.5;
		attackRect.h = attackSize * 2;
	}
	attacking = true;
}

vector2 character::attack(SDL_Rect * enemyRect) {
	bool hit = SDL_HasIntersection(&attackRect, enemyRect);
	if (hit) {
		double xDir = x + w * 0.5 - enemyRect->x + enemyRect->w * 0.5;
		std::cout << xDir << std::endl;
		double yDir = attackRect.y + attackRect.h * 0.5 - enemyRect->y + enemyRect->h * 0.5;
		return vector2(-xDir, -yDir).normalize(attackForce);
	}
	return vector2(0, 0);
}

void character::fixedUpdate() {
	int moveInput = (moveLeft ? -1 : 0) + (moveRight ? 1 : 0);
	if (moveInput > 0) {
		facingRight = true;
	}
	else if (moveInput < 0) {
		facingRight = false;
	}
	double move = xSpeed * moveInput;
	x += move;
	ys += GRAVITY;
	y += ys;
	if (willDash && canDash) {
		int upDownInput = (aimUp ? -1 : 0) + (aimDown ? 1 : 0);
		dashX = moveInput * dashXSpeed;
		dashY = upDownInput * dashYSpeed;
		if (dashX == 0 && dashY == 0) {
			dashX = (facingRight ? 1 : -1) * dashXSpeed;
		}
		if (ys > 0) {
			ys = 0;
		}
		willDash = false;
		canDash = false;
	}
	if (willJump && canJump) {
		ys = -jumpSpeed;
		willJump = false;
	}
	if (abs(dashX) > 0) {
		x += dashX;
		dashX *= dashXDecay;
	}
	if (abs(dashY) > 0) {
		y += dashY;
		dashY *= dashYDecay;
	}
}

void character::collide(double width, double height) {
	character::canJump = false;

	if (character::y > height) {
		character::setPlatform(height);
	}
	if (character::x < 0) {
		character::x = 0;
	}
	if (character::x > width - character::w) {
		character::x = width - character::w;
	}
}

void character::setPlatform(double yPos) {
	y = yPos;
	ys = 0;
	canJump = true;
	canDash = true;
}

void character::render(SDL_Renderer * renderer) {
	SDL_Rect rect;
	int height = static_cast<int>(h);
	if (aimDown) {
		height /= 2;
	}
	rect.x = static_cast<int>(x);
	rect.y = static_cast<int>(y - height);
	rect.w = static_cast<int>(w);
	rect.h = static_cast<int>(height);
	SDL_SetRenderDrawColor(renderer, 71, 71, 255, 255);
	SDL_RenderCopy(renderer, texture, NULL, &rect);

	if (lastAttack < attackDelay - 0.01) {
		SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &attackRect);
		attacking = false;
	}
}