#include "character.h"

const float GRAVITY = 1;

character::character() {
	character(0, 0);
}

character::character(double x, double y) {
	character::x = x;
	character::y = y;
	character::w = 80;
	character::h = 160;
	character::xs = 200;
	character::ys = 0;
	character::moveLeft = 0;
	character::moveRight = 0;
	character::canJump = true;
	character::willJump = false;
	character::jumpSpeed = 0.5;
}

void character::update(double deltaTime) {
	if (character::y > 720) {
		character::y = 720;
		character::ys = 0;
		character::canJump = true;
	}
	else {
		character::canJump = false;
	}
	int moveInput = character::moveLeft ? -1 : 0 + character::moveRight ? 1 : 0;
	double move = character::xs * moveInput * deltaTime;
	character::x += move;
	character::ys += GRAVITY * deltaTime;
	if (character::willJump && character::canJump) {
		character::ys -= character::jumpSpeed;
		character::canJump = false;
	}
	character::y += character::ys;
}

void character::render(SDL_Renderer * renderer) {
	SDL_Rect rect;
	rect.x = character::x - character::w / 2;
	rect.y = character::y - character::h;
	rect.w = character::w;
	rect.h = character::h;
	SDL_SetRenderDrawColor(renderer, 71, 71, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}