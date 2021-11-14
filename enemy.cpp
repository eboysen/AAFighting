#include "enemy.h"

const float GRAVITY = 1.5;

enemy::enemy() {
	enemy(0, 0);
}

enemy::enemy(double x, double y) {
	enemy::action = EnemyActions::Idle;
	enemy::x = x - 40;
	enemy::y = y;
	enemy::w = 80;
	enemy::h = 160;
	enemy::ys = 0;
	enemy::willJump = false;
	enemy::canJump = false;
	enemy::jumpSpeed = 0.6;
}

void enemy::think(character* player) {
	int horzSeperation = 0;// enemy::x - player.x;
	int vertSeperation = 0;// enemy::y - player.y;
	switch (enemy::action) {
	case EnemyActions::Idle:
		if (abs(horzSeperation) > 350) {
			// Move towards player
			enemy::action = EnemyActions::MoveTowards;
		}
		else if (abs(horzSeperation) < 50) {
			// Move away from player
			// Block?
			enemy::action = EnemyActions::MoveAway;
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
	rect.x = static_cast<int>(enemy::x);
	rect.y = static_cast<int>(enemy::y - enemy::h);
	rect.w = static_cast<int>(enemy::w);
	rect.h = static_cast<int>(enemy::h);
	SDL_SetRenderDrawColor(renderer, 255, 71, 71, 255);
	SDL_RenderFillRect(renderer, &rect);
}