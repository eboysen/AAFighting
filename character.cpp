#include "character.h"

const float GRAVITY = 1.5;

character::character() {
	character(0, 0);
}

character::character(double x, double y) {
	character::x = x - 40;
	character::y = y;
	character::w = 80;
	character::h = 160;
	character::moveX = 200;
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