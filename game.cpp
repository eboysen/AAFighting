#include "game.h"

const double FIXED_UPDATE_TIME = 0.02;

game::game(Uint16 width, Uint16 height) {
	game::active = true;
	game::window_width = width;
	game::window_height = height;
	game::window = SDL_CreateWindow("AAFighter", 100, 100, width, height, SDL_WINDOW_OPENGL);
	game::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	game::player = character::character(width * 0.2, height * 0.8);
	game::enemy = enemy::enemy(width * 0.8, height * 0.8);
	game::now = SDL_GetPerformanceCounter();
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
			return;
		}
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				game::player.moveLeft = true;
				break;
			case SDLK_RIGHT:
				game::player.moveRight = true;
				break;
			case SDLK_UP:
				game::player.aimUp = true;
				break;
			case SDLK_DOWN:
				game::player.aimDown = true;
				break;
			case SDLK_SPACE:
				game::player.willJump = true;
				break;
			case SDLK_x:
				game::player.willDash = true;
				break;
			case SDLK_z:
				game::player.willAttack = true;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				game::player.moveLeft = false;
				break;
			case SDLK_RIGHT:
				game::player.moveRight = false;
				break;
			case SDLK_UP:
				game::player.aimUp = false;
				break;
			case SDLK_DOWN:
				game::player.aimDown = false;
				break;
			case SDLK_SPACE:
				game::player.willJump = false;
				break;
			case SDLK_x:
				game::player.willDash = false;
				break;
			case SDLK_z:
				game::player.willAttack = false;
				break;
			}
			break;
		}
	}
	game::last = game::now;
	game::now = SDL_GetPerformanceCounter();
	double deltaTime = ((game::now - game::last) / (double)SDL_GetPerformanceFrequency());

	game::currentTime += deltaTime;
	while (game::currentTime > FIXED_UPDATE_TIME) {
		game::currentTime -= FIXED_UPDATE_TIME;
		game::player.fixedUpdate();
		game::player.collide(game::window_width, game::window_height);
	}

	game::player.update(deltaTime);
	game::enemy.think(&(game::player));
	game::enemy.update(deltaTime);
	game::enemy.collide(game::window_width, game::window_height);

	game::back->platformCheck(& player);
}

void game::render() {
	SDL_SetRenderDrawColor(game::renderer, 71, 71, 71, 255);
	SDL_RenderClear(game::renderer);
	game::back->renderEnvironment(game::renderer,game::window_width,game::window_height);
	game::enemy.render(game::renderer);
	game::player.render(game::renderer);
	SDL_RenderPresent(game::renderer);
}

