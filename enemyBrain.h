#pragma once

#include "entity.h"

class enemyBrain
{
private:
	static enum EnemyAction {
		Idle,
		MoveAway,
		MoveTowards,
		DashTowards,
		DashAway,
		Attack
	};
	EnemyAction action;
	double attackTime;
public:
	enemyBrain();
	void think(entity* self, entity* other, double deltaTime);
};

