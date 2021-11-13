#include "game.h"

game::game() {
	game::active = true;
	game::window = SDL_CreateWindow("AAFighter", 200, 200, 400, 600, SDL_WINDOW_OPENGL);
	game::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

game::~game() {
	SDL_DestroyRenderer(game::renderer);
	SDL_DestroyWindow(game::window);
	SDL_Quit();
}

void game::update() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			game::active = false;
		}
	}
}

void game::render() {

}

