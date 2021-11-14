#include "rain.h"

rain::rain() {}
rain::rain(int x, int y, int h) {
	rain::x = x;
	rain::y = y;
	rain::h = h;
	rain::ys = (double)(rand() % 40) + 300;
	rain::b = rand() % 60 + 51;
	rain::rect = SDL_Rect();
	rain::rect.x = x;
	rain::rect.y = y;
	rain::rect.w = 1;
	rain::rect.h = 4 + rand() % 8;
}

void rain::update(double deltaTime) {
	y += ys * deltaTime;
	if (y > h) {
		y = -rect.h;
	}
	rect.y = y;
}

void rain::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 26, 21, b, 255);
	SDL_RenderDrawRect(renderer, &rect);
}