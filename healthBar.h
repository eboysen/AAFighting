#pragma once
#include <cmath>

#include "SDL.h"
#include "TextureManager.h"

class healthBar
{
public:
	healthBar();
	healthBar(SDL_Renderer* renderer, SDL_Rect rect, int maxHealth, bool leftAlign);
	void setHealth(int health);
	void update(double deltaTime);
	void render(SDL_Renderer* renderer);
	SDL_Rect getBarRect(int i);
private:
	SDL_Texture* bar;
	SDL_Rect rect;
	bool leftAlign;
	int maxHealth;
	int currentHealth;
	double damageEffectValue;
	double fadeDamageEffect;
	double fadeDamageSpeed;
	double lastHealthChangeTime = 0;
};

