#include "enemyBrain.h"
#include <iostream>

enemyBrain::enemyBrain() {
	action = Idle;
}

void enemyBrain::think(entity* self, entity* other) {
	int horzSeperation = self->getX() - other->getX();
	int vertSeperation = self->getX() - other->getY();
	int maxIdle = 10;
	if (self->getX() < 50) {
		self->input(self->Right, true);
		self->input(self->Left, false);
		action = EnemyAction::Idle;
		return;
	}
	if (self->getX() >1100) {
		self->input(self->Left, true);
		self->input(self->Right, false);
		action = EnemyAction::Idle;
		return;
	}
	switch (action) {
	case EnemyAction::Idle:
		maxIdle--;
		self->input(self->Attack, false);
		self->input(self->Dash, false);
		self->input(self->Down, false);
		self->input(self->Jump, false);
		self->input(self->Left, false);
		self->input(self->Right, false);
		self->input(self->Special, false);
		self->input(self->Up, false);
		
		
		if (abs(horzSeperation) < 50) {
			// Move away from player
			// Block?
			self->input(self->Attack, true);
			if (rand() % 2 == 1)
				action = EnemyAction::MoveAway;
			else
				action = EnemyAction::Attack;
		}
		else if (abs(horzSeperation) > 350 || rand() % 2 == 1) {
		// Move towards player

		action = MoveTowards;
		// ACTIONS
		}
		else if (vertSeperation > 100) {
			
			action = EnemyAction::DashTowards;
			// Jump
		}
		else if (vertSeperation < -100) {
			// Downwards attack
		}
		else {
			action = EnemyAction::Attack;
		}
		break;
	case EnemyAction::MoveTowards:
		
		if (horzSeperation > 0) {
			self->input(self->Left,true);
		}
		else {
			self->input(self->Right, true);
		}
		if (abs(horzSeperation < 50)) {
			action = EnemyAction::Idle;
		}
		break;
	case EnemyAction::MoveAway:
		
		if (horzSeperation > 0) {
			self->input(self->Right, true);
		}
		else {
			self->input(self->Left, true);
		}
		if (abs(horzSeperation) > 150) {
			action = EnemyAction::Idle;
		}
		break;
	case EnemyAction::DashTowards:
		
		if (horzSeperation > 100) {
			self->input(self->Left, true);
		}
		else if (horzSeperation < -100) {
			self->input(self->Right, true);
		}
		if (vertSeperation > 0) {
			self->input(self->Up, true);
		}
		self->input(self->Dash, true);
		if (abs(vertSeperation) < 100) {
			self->input(self->Attack, true);
		}
		action = EnemyAction::Idle;
		break;
	case EnemyAction::Attack:
		
		
		self->input(self->Attack, true);
		
		if (abs(horzSeperation) > 50) {
			action = EnemyAction::Idle;
		}
		else {
			if (rand() % 2 == 1) {
				self->input(self->Down, true);
			}
			if (horzSeperation > 0) {
				self->input(self->Left, true);
			}
			else
				self->input(self->Right, true);
		}
	}
	
}
