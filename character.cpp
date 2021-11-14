#include "character.h"
#include <iostream>

const float GRAVITY = 1.4;

character::character() {
	character(0, 0);
}

character::character(double x, double y) {
	character::x = x - 40;
	character::y = y;
	character::w = 80;
	character::h = 160;
	character::xSpeed = 10;
	character::dashSpeed = 36;
	character::dashDecay = 0.9;
	character::jumpSpeed = 20;
}

void character::update(double deltaTime) {
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
	if (willDash) {
		int upDownInput = (aimUp ? -1 : 0) + (aimDown ? 1 : 0);
		dashX = moveInput * dashSpeed;
		dashY = upDownInput * dashSpeed;
		if (dashX == 0 && dashY == 0) {
			dashX = (facingRight ? 1 : -1) * dashSpeed;
		}
		ys = 0;
		willDash = false;
	}
	if (willJump && canJump) {
		ys = -jumpSpeed;
		willJump = false;
	}
	if (abs(dashX) > 0) {
		x += dashX;
		dashX *= character::dashDecay;
	}
	if (abs(dashY) > 0) {
		y += dashY;
		dashY *= character::dashDecay;
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
	character::y = yPos;
	character::ys = 0;
	character::canJump = true;
}

void character::render(SDL_Renderer * renderer) {
	SDL_Rect rect;
	rect.x = static_cast<int>(character::x);
	rect.y = static_cast<int>(character::y - character::h);
	rect.w = static_cast<int>(character::w);
	rect.h = static_cast<int>(character::h);
	SDL_SetRenderDrawColor(renderer, 71, 71, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}