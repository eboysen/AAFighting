#include "healthBar.h"
#include <iostream>

healthBar::healthBar() {
	healthBar(nullptr, SDL_Rect(), 0, 0);
}
healthBar::healthBar(SDL_Renderer * renderer, SDL_Rect rect, int maxHealth, bool leftAlign) {
	bar = TextureManager::loadTexture("./assets/healthBar.png", renderer);
	healthBar::rect = rect;
	healthBar::leftAlign = leftAlign;
	healthBar::maxHealth = maxHealth;
	healthBar::damageEffectValue = maxHealth;
	healthBar::currentHealth = maxHealth;
	healthBar::fadeDamageEffect = 0.33;
	healthBar::fadeDamageSpeed = 25;
}
void healthBar::setHealth(int health) {
	if (health == currentHealth) return;
	currentHealth = health;
	lastHealthChangeTime = 0;
}
void healthBar::update(double deltaTime) {
	lastHealthChangeTime += (double)deltaTime;
	if (lastHealthChangeTime > fadeDamageEffect && damageEffectValue > currentHealth) {
		damageEffectValue -= deltaTime * fadeDamageSpeed;
	}
}
void healthBar::render(SDL_Renderer * renderer) {
	double delta2 = damageEffectValue / maxHealth;
	double delta1 = (double)currentHealth / maxHealth;
	SDL_Rect barRect = SDL_Rect();
	barRect.x = rect.x;
	barRect.y = rect.y;
	barRect.w = rect.w * delta1;
	barRect.h = rect.h;
	SDL_Rect srcRect = getBarRect(0);
	SDL_RenderCopy(renderer, bar, &srcRect, &barRect);

	barRect = SDL_Rect();
	barRect.x = rect.x + rect.w * delta1;
	barRect.y = rect.y;
	barRect.w = rect.w * (delta2 - delta1);
	barRect.h = rect.h;
	srcRect = getBarRect(1);
	SDL_RenderCopy(renderer, bar, &srcRect, &barRect);
	
	barRect = SDL_Rect();
	barRect.x = rect.x + rect.w * delta2;
	barRect.y = rect.y;
	barRect.w = rect.w - rect.w * delta2;
	barRect.h = rect.h;
	srcRect = getBarRect(2);
	SDL_RenderCopy(renderer, bar, &srcRect, &barRect);
}
SDL_Rect healthBar::getBarRect(int i) {
	SDL_Rect barRect = SDL_Rect();
	barRect.x = 0;
	barRect.y = 16 * i;
	barRect.w = 64;
	barRect.h = 16;
	return barRect;
}