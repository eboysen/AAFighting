#include "entityRenderer.h"
#include <iostream>

entityRenderer::entityRenderer() {
}
entityRenderer::entityRenderer(SDL_Renderer* renderer, entitySet set) {
	entityRenderer::set = set;
	walkingTexture = TextureManager::loadTexture(set.walkFilePath, renderer);
	entityRenderer::crouch = false;
	entityRenderer::width = 80;
	entityRenderer::heightStanding = 120;
	entityRenderer::heightCrouching = 80;
}
void entityRenderer::handleMovement(double deltaTime, double leftRight) {
	if (leftRight != 0) {
		lastWalkTime += deltaTime;
		if (lastWalkTime > set.walkTimeDelay) {
			lastWalkTime = 0;
			if (++walkingIndex >= set.maxWalkIndex) {
				walkingIndex = 0;
			}
		}
	}
}
void entityRenderer::handleJump() {

}
void entityRenderer::render(SDL_Renderer* renderer, bool facingRight, double x, double y) {
	SDL_Rect rect = getEntityRect(x, y);

	SDL_SetRenderDrawColor(renderer, 71, 71, 255, 255);
	SDL_Rect srcRect = getWalkingRect();
	if (facingRight) {
		
		SDL_RenderCopy(renderer, walkingTexture, &srcRect,&rect);
	}
	else {
		SDL_RenderCopyEx(renderer, walkingTexture, &srcRect, &rect, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
}
SDL_Rect entityRenderer::getEntityRect(double x, double y) {
	SDL_Rect rect;
	int height = static_cast<int>(getHeight());
	rect.x = static_cast<int>(x);
	rect.y = static_cast<int>(y - height);
	rect.w = static_cast<int>(getWidth());
	rect.h = static_cast<int>(height);
	return rect;
}
SDL_Rect entityRenderer::getWalkingRect() {
	SDL_Rect rect;
	rect.x = 32 * round(walkingIndex % 2);
	rect.y = 32 * floor(walkingIndex / 2);
	rect.w = 32;
	rect.h = 32;
	return rect;
}