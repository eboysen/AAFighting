#include "enemy.h"
#include <iostream>

const double GRAVITY = 1.4;

enemy::enemy() {}
enemy::enemy(SDL_Renderer* renderer, animationSet set, double x, double y) {
	enemy::texture = TextureManager::loadTexture(set.filePath, renderer);
	enemy::action = EnemyActions::Idle;
	enemy::x = x - 40;
	enemy::y = y;
	enemy::w = 80;
	enemy::h = 120;
	enemy::xs = 0;
	enemy::ys = 0;
	enemy::xSpeed = 10;
	enemy::willJump = false;
	enemy::canJump = false;
	enemy::jumpSpeed = 0.6;
	enemy::maxWalkIndex = set.maxAnimationFrames;
	enemy::walkTimeDelay = set.animationFrameDelay;
}

void enemy::think(character* player) {
	int horzSeperation = x - player->getX();
	int vertSeperation = y - player->getY();
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
	int leftRight = -1; //TODO: Add movement
	if (leftRight != 0) {
		lastWalkTime += deltaTime;
		if (lastWalkTime > walkTimeDelay) {
			lastWalkTime = 0;
			if (++walkingIndex >= maxWalkIndex) {
				walkingIndex = 0;
			}
		}
	}
}

void enemy::fixedUpdate() {
	int moveInput = 0; //TODO: Add movement
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
	ys += y;
}

void enemy::render(SDL_Renderer* renderer) {
	SDL_Rect rect = getRect();
	SDL_SetRenderDrawColor(renderer, 255, 71, 71, 255);
	SDL_Rect srcRect;
	std::cout << walkingIndex << std::endl;
	srcRect.x = 32 * round(walkingIndex % 2);
	srcRect.y = 32 * floor(walkingIndex / 2);
	srcRect.w = 32;
	srcRect.h = 32;
	if (facingRight) {
		SDL_RenderCopy(renderer, texture, &srcRect, &rect);
	}
	else {
		SDL_RenderCopyEx(renderer, texture, &srcRect, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
}

SDL_Rect enemy::getRect() {
	SDL_Rect rect;
	rect.x = static_cast<int>(x);
	rect.y = static_cast<int>(y - h);
	rect.w = static_cast<int>(w);
	rect.h = static_cast<int>(h);
	return rect;
}