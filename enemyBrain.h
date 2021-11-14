#pragma once

#include "entity.h"

class enemyBrain
{
private:
	static enum EnemyAction {
		Idle,
		MoveAway,
		MoveTowards
	};
	EnemyAction action;
public:
	enemyBrain();
	void think(entity* self, entity* other);
};

