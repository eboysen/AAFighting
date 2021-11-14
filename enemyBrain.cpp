#include "enemyBrain.h"

enemyBrain::enemyBrain() {
	action = Idle;
}

void enemyBrain::think(entity* self, entity* other) {
	int horzSeperation = self->getX() - other->getX();
	int vertSeperation = self->getX() - other->getY();
	switch (action) {
	case EnemyAction::Idle:
		if (abs(horzSeperation) > 350) {
			// Move towards player
			action = MoveTowards;
			// ACTIONS
			self->input(self->Left, true);
		}
		else if (abs(horzSeperation) < 50) {
			// Move away from player
			// Block?
			action = EnemyAction::MoveAway;
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
	case EnemyAction::MoveTowards:
		break;
	case EnemyAction::MoveAway:
		break;
	}
}
