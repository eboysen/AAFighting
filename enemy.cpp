#include "enemy.h"

const float GRAVITY = 1.5;

enemy::enemy() {
	enemy(0, 0);
}

enemy::enemy(double x, double y) {
	enemy::x = x - 40;
	enemy::y = y;
	enemy::w = 80;
	enemy::h = 160;
	enemy::ys = 0;
	enemy::willJump = false;
	enemy::canJump = false;
	enemy::jumpSpeed = 0.6;
}

void enemy::update(double deltaTime) {
	enemy::ys += GRAVITY * deltaTime;
	if (enemy::willJump && enemy::canJump) {
		enemy::ys = -enemy::jumpSpeed;
		enemy::willJump = false;
	}
	enemy::y += enemy::ys;
}

void enemy::collide(double width, double height) {
	enemy::canJump = false;

	if (enemy::y > height) {
		enemy::y = height;
		enemy::ys = 0;
		enemy::canJump = true;
	}
	if (enemy::x < 0) {
		enemy::x = 0;
	}
	if (enemy::x > width - enemy::w) {
		enemy::x = width - enemy::w;
	}
}

void enemy::render(SDL_Renderer* renderer) {
	SDL_Rect rect;
	rect.x = enemy::x;
	rect.y = enemy::y - enemy::h;
	rect.w = enemy::w;
	rect.h = enemy::h;
	SDL_SetRenderDrawColor(renderer, 255, 71, 71, 255);
	SDL_RenderFillRect(renderer, &rect);
}