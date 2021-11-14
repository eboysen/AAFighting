#include "enemy.h"
#include <iostream>

const float GRAVITY = 1.4;

enemy::enemy() {}
enemy::enemy(double x, double y) {
	enemy::action = EnemyActions::Idle;
	enemy::x = x - 40;
	enemy::y = y;
	enemy::w = 80;
	enemy::h = 160;
	enemy::xs = 0;
	enemy::ys = 0;
	enemy::willJump = false;
	enemy::canJump = false;
	enemy::jumpSpeed = 0.6;
}

void enemy::think(character* player) {
	int horzSeperation = 0;// enemy::x - player.x;
	int vertSeperation = 0;// enemy::y - player.y;
	switch (action) {
	case EnemyActions::Idle:
		if (abs(horzSeperation) > 350) {
			// Move towards player
			action = EnemyActions::MoveTowards;
		}
		else if (abs(horzSeperation) < 50) {
			// Move away from player
			// Block?
			action = EnemyActions::MoveAway;
		}
		else if (vertSeperation > 100) {
			// Jump
		}
		else if (vertSeperation < -100) {
			// Downwards attack
		}
		else {
			// Attack
		}
		break;
	case EnemyActions::MoveTowards:
		break;
	case EnemyActions::MoveAway:
		break;
	}
}

void enemy::update(double deltaTime) {
}

void enemy::fixedUpdate() {
	/*
	int moveInput = (moveLeft ? -1 : 0) + (moveRight ? 1 : 0);
	if (moveInput > 0) {
		facingRight = true;
	}
	else if (moveInput < 0) {
		facingRight = false;
	}
	double move = xSpeed * moveInput;
	x += move;
	*/
	ys += GRAVITY;
	y += ys;
	if (xs > 0.01 || xs < 0.01) {
		x += xs;
		xs *= 0.6;
	}
}

void enemy::collide(double width, double height) {
	canJump = false;

	if (y > height) {
		enemy::setPlatform(height);
	}
	if (x < 0) {
		x = 0;
	}
	if (x > width - w) {
		x = width - w;
	}
}

void enemy::setPlatform(double yPos) {
	y = yPos;
	ys = 0;
	canJump = true;
}

void enemy::applyKickback(double x, double y) {
	xs += x;
	ys += y / 2;
}

void enemy::render(SDL_Renderer* renderer) {
	SDL_Rect rect = getRect();
	SDL_SetRenderDrawColor(renderer, 255, 71, 71, 255);
	SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect enemy::getRect() {
	SDL_Rect rect;
	rect.x = static_cast<int>(x);
	rect.y = static_cast<int>(y - h);
	rect.w = static_cast<int>(w);
	rect.h = static_cast<int>(h);
	return rect;
}