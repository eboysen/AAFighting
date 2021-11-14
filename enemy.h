#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "character.h"

enum EnemyActions {
	Idle,
	MoveAway,
	MoveTowards,
};

class enemy
{
public:
	enemy();
	enemy(double x, double y);
	void think(character* player);
	void update(double deltaTime);
	void fixedUpdate();
	void collide(double width, double height);
	void setPlatform(double yPos);
	void applyKickback(double x, double y);
	void render(SDL_Renderer* renderer);
	bool willJump;
	SDL_Rect getRect();
private:
	EnemyActions action;
	double x;
	double y;
	double w;
	double h;

	double xs;
	double ys;

	bool canJump;
	double jumpSpeed;
};

