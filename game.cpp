#include "game.h"

const double FIXED_UPDATE_TIME = 0.02;

game::game(Uint16 width, Uint16 height) {
	game::active = true;
	game::window_width = width;
	game::window_height = height;
	game::window = SDL_CreateWindow("AAFighter", 100, 100, width, height, SDL_WINDOW_OPENGL);
	game::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	game::player = character::character(renderer, width * 0.2, height * 0.8);
	game::enemy = enemy::enemy(width * 0.8, height * 0.8);
	game::now = SDL_GetPerformanceCounter();
	game::environment = environment::environment(renderer);
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
			active = false;
			return;
		}
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				player.moveLeft = true;
				break;
			case SDLK_RIGHT:
				player.moveRight = true;
				break;
			case SDLK_UP:
				player.aimUp = true;
				break;
			case SDLK_DOWN:
				player.aimDown = true;
				break;
			case SDLK_SPACE:
				player.willJump = true;
				break;
			case SDLK_x:
				player.willDash = true;
				break;
			case SDLK_z:
				player.willAttack = true;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				player.moveLeft = false;
				break;
			case SDLK_RIGHT:
				player.moveRight = false;
				break;
			case SDLK_UP:
				player.aimUp = false;
				break;
			case SDLK_DOWN:
				player.aimDown = false;
				break;
			case SDLK_SPACE:
				player.willJump = false;
				break;
			case SDLK_x:
				player.willDash = false;
				break;
			case SDLK_z:
				player.willAttack = false;
				player.canAttack = true;
				break;
			}
			break;
		}
	}
	last = now;
	now = SDL_GetPerformanceCounter();
	double deltaTime = ((now - last) / (double)SDL_GetPerformanceFrequency());

	currentTime += deltaTime;
	while (currentTime > FIXED_UPDATE_TIME) {
		currentTime -= FIXED_UPDATE_TIME;
		player.fixedUpdate();
		player.collide(window_width, window_height);
		enemy.fixedUpdate();
		enemy.collide(window_width, window_height);
	}

	player.update(deltaTime);
	if (player.isAttacking()) {
		vector2 kickback = player.attack(enemy.getRect());
		enemy.applyKickback(kickback.x, kickback.y);
	}
	enemy.think(&(player));

	environment.platformCheck(& player);
}

void game::render() {
	SDL_SetRenderDrawColor(renderer, 71, 71, 71, 255);
	SDL_RenderClear(renderer);
	environment.renderEnvironment(renderer,window_width,window_height);
	enemy.render(renderer);
	player.render(renderer);
	
	SDL_RenderPresent(renderer);
}

