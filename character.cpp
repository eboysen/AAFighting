#include "character.h"

const float GRAVITY = 1.5;

character::character() {
	character(0, 0);
}

character::character(double x, double y) {
	character::x = x;
	character::y = y;
	character::w = 80;
	character::h = 160;
	character::moveX = 200;
	character::xs = 0;
	character::ys = 0;
	character::moveLeft = 0;
	character::moveRight = 0;
	character::willJump = false;
	character::canJump = false;
	character::jumpSpeed = 0.6;
}

void character::update(double deltaTime) {
	int moveInput = character::moveLeft ? -1 : 0 + character::moveRight ? 1 : 0;
	double move = character::moveX * moveInput * deltaTime;
	character::x += move;
	if (character::xs > 0.001 || character::xs < -0.001) {
		character::x += character::xs;
		character::xs *= 0.9;
	}
	character::ys += GRAVITY * deltaTime;
	if (character::willJump && character::canJump) {
		character::ys = -character::jumpSpeed;
		character::willJump = false;
	}
	character::y += character::ys;
}

void character::collide(double width, double height) {
	character::canJump = false;

	if (character::y > height) {
		character::y = height;
		character::ys = 0;
		character::canJump = true;
	}
	double halfWidth = character::w * 0.5;
	if (character::x - halfWidth < 0) {
		character::x = halfWidth;
	}
	if (character::x + halfWidth > width) {
		character::x = width - halfWidth;
	}
}

void character::render(SDL_Renderer * renderer) {
	SDL_Rect rect;
	rect.x = character::x - character::w * 0.5;
	rect.y = character::y - character::h;
	rect.w = character::w;
	rect.h = character::h;
	SDL_SetRenderDrawColor(renderer, 71, 71, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}