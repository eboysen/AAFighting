#pragma once

#include "TextureManager.h"
#include "entitySet.h"
#include "SDL.h"
#include "SDL_image.h"

class entityRenderer
{
public:
	// Constructors
	entityRenderer();
	entityRenderer(SDL_Renderer* renderer, entitySet set);

	// Handlers
	void handleMovement(double deltaTime, double leftRight);
	void handleJump();

	// Render
	void render(SDL_Renderer* renderer, bool facingRight, double x, double y);

	// Helpers
	SDL_Rect getEntityRect(double x, double y);
	SDL_Rect getWalkingRect();

	// Parameters
	bool crouch;
	double getWidth() { return width; }
	double getHeight() { return crouch ? heightCrouching : heightStanding; }
private:
	entitySet set;

	// Base texture
	SDL_Texture* walkingTexture;

	// Bounds
	double width;
	double heightStanding;
	double heightCrouching;

	// Walking
	double lastWalkTime = 0;
	int walkingIndex = 0;
};

