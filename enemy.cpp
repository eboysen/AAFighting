#include "enemy.h"

const float GRAVITY = 1.5;

enemy::enemy() {
	enemy(0, 0);
}

enemy::enemy(double x, double y) {
	enemy::x = x;
	enemy::y = y;
	enemy::w = 80;
	enemy::h = 160;
	enemy::moveX = 200;
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
	double halfWidth = enemy::w * 0.5;
	if (enemy::x - halfWidth < 0) {
		enemy::x = halfWidth;
	}
	if (enemy::x + halfWidth > width) {
		enemy::x = width - halfWidth;
	}
}

void enemy::render(SDL_Renderer* renderer) {
	SDL_Rect rect;
	rect.x = enemy::x - enemy::w * 0.5;
	rect.y = enemy::y - enemy::h;
	rect.w = enemy::w;
	rect.h = enemy::h;
	SDL_SetRenderDrawColor(renderer, 255, 71, 71, 255);
	SDL_RenderFillRect(renderer, &rect);
}